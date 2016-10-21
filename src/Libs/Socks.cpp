/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Socks.cpp
 * @ingroup		general
 * @author		Patricio A. Rossi (MeduZa)
 * 
 * @copyright	Copyright © 2015 - 2016 Patricio A. Rossi (MeduZa)
 *
 * @copyright	lcdspicer2 is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * @copyright	lcdspicer2 is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * @copyright	You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Socks.hpp"
#include "Error.hpp"

#define BUFFER_SIZE 1024
#include <unistd.h> //for close
#include <netdb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <cstring>

using namespace LCDSpicer2;

/**
 * Creates a new socked connection to hostAddress on the port hostPort.
 *
 * @param[in] hostAddress IP address.
 * @param[in] hostPort port number.
 * @throws LCDSpicer2::Error if fails to connect.
 */
Socks::Socks(const string& hostAddress, const string& hostPort) {
	connect(hostAddress, hostPort);
}

void Socks::connect(const string& hostAddress, const string& hostPort) {

	if (connected)
		throw Error("Already connected.");

	addrinfo hints, *servinfo;
	hints.ai_family		= AF_INET; //AF_INET AF_UNSPEC;
	hints.ai_protocol	= IPPROTO_TCP;
	hints.ai_socktype	= SOCK_STREAM;
	hints.ai_flags		= AI_CANONNAME;//AI_PASSIVE;

	errcode = getaddrinfo(hostAddress.c_str(), hostPort.c_str(), &hints, &servinfo);

	if (errcode) {
		freeaddrinfo(servinfo);
		throw Error("Unable to find the server " + hostAddress + ", port " + hostPort + " " + gai_strerror(errcode));
	}

	sockFB = socket(
		servinfo->ai_family,
		servinfo->ai_socktype,
		servinfo->ai_protocol
	);

	if (sockFB == -1) {
		::close(sockFB);
		freeaddrinfo(servinfo);
		throw Error("Failed to create socket " + string(strerror(errno)));
	}

	if (::connect(sockFB, servinfo->ai_addr, servinfo->ai_addrlen)) {
		::close(sockFB);
		freeaddrinfo(servinfo);
		throw Error("Failed to connect to the server " + hostAddress + ", port " + hostPort + " " + string(strerror(errno)));
	}

	freeaddrinfo(servinfo);
	connected = true;
}

bool Socks::send(const string& message) throw() {

	if (not connected)
		return false;

	if (message.empty())
		return true;

	errcode = ::send(sockFB, message.c_str(), message.length(), 0);
	if (errcode == message.length()) {
		errcode = 0;
		return true;
	}
	return false;
}

bool Socks::recive(string& buffer) throw() {

	buffer.clear();

	if (not connected)
		return false;

	int on = 1;
	ssize_t n = 0;

	fd_set readset;
	FD_ZERO(&readset);
	FD_SET(sockFB, &readset);

//	if ( == -1) return false;
	ioctl(sockFB, FIONBIO, (char*) &on);

	// Check if there is any data to read.
	n = select(sockFB + 1, NULL, &readset, NULL, NULL);
	if (n <= 0)
		// There is nothing to receive (or error).
		return true;

	char* bufferp = new char[BUFFER_SIZE];
	n = recv(sockFB, bufferp, BUFFER_SIZE, 0); // MSG_DONTWAIT;
	if (n < 0)
		errcode = n;

	if (n > 0) {
		bufferp[n] = '\0';
		buffer = string(bufferp);
	}
	delete[] bufferp;
	return (n >= 0);
}

void Socks::disconnect() {
	if (connected) {
		::close(sockFB);
		connected = false;
	}
}

Socks::~Socks() {
	disconnect();
}

