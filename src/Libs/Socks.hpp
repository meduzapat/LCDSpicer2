/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Socks.hpp
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

#ifndef SRC_LIBS_SOCKS_HPP_
#define SRC_LIBS_SOCKS_HPP_ 1

// To use strings
#include <string>
using std::string;

namespace LCDSpicer2 {

/**
 * Socks
 *
 * Class to handle IP connections using sockets.
 */
class Socks {

public:

	/**
	 * Creates a new socket instance, but does not connect.
	 */
	Socks() {}

	/**
	 * Creates a new socked connection to hostAddress on the port hostPort.
	 *
	 * @param[in] hostAddress IP address.
	 * @param[in] hostPort port number.
	 * @throws LCDSpicer2::Error if fails to connect.
	 */
	Socks(const string& hostAddress, const string& hostPort);

	/**
	 * Creates a new socked connection to hostAddress on the port hostPort.
	 *
	 * @param[in] hostAddress IP address.
	 * @param[in] hostPort port number.
	 * @throws LCDSpicer2::Error if something goes wrong.
	 */
	void connect(const string& hostAddress, const string& hostPort);

	/**
	 * Checks if is connected.
	 *
	 * @return boolean true if connected.
	 */
	bool isConnected() {
		return connected;
	}

	/**
	 * Sends message.
	 *
	 * @param[in] message a string to send to the sock.
	 * @return true on success, false on fail, if the message is empty will return true but nothing will be done.
	 */
	bool send(const string& message) throw();

	/**
	 * Retrieves message.
	 *
	 * @param[out] buffer
	 * @return boolean true on success, false on fail, if nothing is received true is return.
	 */
	bool recive(string& buffer) throw();

	/**
	 * Returns the last generated error code.
	 *
	 * @return a sock error code.
	 */
	int getErrorCode() {
		return errcode;
	}

	/**
	 * Closes the connection.
	 */
	void disconnect();

	/**
	 * Clean up.
	 */
	~Socks();

private:

	/// Stores the last generated error code or 0 if none.
	int errcode		= 0;

	/// Open connection flag.
	bool connected	= false;

	/// Socket frame buffer.
	int sockFB		= 0;

};

}

#endif // SRC_LIBS_SOCKS_HPP_
