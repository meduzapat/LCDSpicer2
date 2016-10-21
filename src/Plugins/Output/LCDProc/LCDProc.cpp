/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LCDProc.cpp
 * @ingroup		LCDProcOutputPlugin
 * @since		Jan 16, 2016
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

#include "LCDProc.hpp"
#include "Socks.hpp"

// Plugin factory functions.
#ifdef outputPluginFactory
	outputPluginFactory(LCDProc)
#else
	#error "Plugin factory function missing."
#endif

LCDProc::~LCDProc() {
	LOG(LCDSpicer2::Logger::DEBUG, "LCDProc Destroyed");
}

bool LCDProc::initialize() {

	LOG(LCDSpicer2::Logger::DEBUG, "LCDProc Created");

	// Read configuration.
	string server, port;
	LCDSpicer2::Value val;
	if (getConfigurationValue("Server", val))
		val.get(server);
	else {
		LOG(LCDSpicer2::Logger::INFO, "Server not defined in the configuration, using default value localhost");
		server = "127.0.0.1";
	}

	if (getConfigurationValue("Port", val))
		val.get(port);
	else {
		LOG(LCDSpicer2::Logger::INFO, "Port number not defined in the configuration, using default value 13666");
		port = "13666";
	}

	if (getConfigurationValue("Commands per message", val))
		commandsToSend = (uint8_t) val.getUInt();

	if (getConfigurationValue("Affinity", val))
		val.get(affinity);

	// Connect to the LCDd.
	try {
		connect(server, port);
	}
	catch (LCDSpicer2::Error& e) {
		LOG(LCDSpicer2::Logger::ERROR, e.what());
		return false;
	}

	if (not send("hello\n")) {
		LOG(LCDSpicer2::Logger::ERROR, "Unable to communicate with LCDd");
		disconnect();
		return false;
	}

	string buffer;

	// Server needs time to start the connection.
	usleep(150000);
	recive(buffer);

	// Necessary elements to extract from the LCDd answer.
	string elements[] = {" lcd wid ", " hgt ", " cellwid ", " cellhgt "};

	uint64_t values[] = {0, 0, 0, 0};

	for (int8_t c = 3; c >= 0; c--) {

		int start = buffer.rfind(elements[c]);

		if (start == string::npos) {
			LOG(LCDSpicer2::Logger::ERROR, "LCDd returned an unknown answer.");
			disconnect();
			return false;
		}

		values[c] = std::stoi(buffer.substr(start + elements[c].size()));
		buffer.resize(start);
	}

	// Set sizes.
	screenSize.setWidth(values[0])->setHeight(values[1]);
	fontSize.setWidth(values[2])->setHeight(values[3]);

	usleep(50000);
	send("client_set -name LCDspicer2\n");

	LOG(LCDSpicer2::Logger::DEBUG, "Screen: " + std::to_string(values[0]) + "x" + std::to_string(values[1]) + ", Font: " + std::to_string(values[2]) + "x" + std::to_string(values[3]));

	return STATUS_OK;
}

uint8_t LCDProc::refresh() {

	if (not isConnected())
		return STATUS_OFFLINE;

	string buffer;

	do {

		// Get answers.
		recive(buffer);

		if (not buffer.empty()) {
//			LOG(LCDSpicer2::Logger::DEBUG, "Received: " + buffer);

			// Report errors (only for warning level).
			if (logger->isLogging(LCDSpicer2::Logger::WARNING))
				processAnswer(buffer, "huh? ");

			// Check buttons.
			processAnswer(buffer, "key ");
		}

		if (messagesPool.empty())
			break;

		// Send a pack of messages to the LCDd server.
		buffer.clear();

		// Create a pack.
		for (size_t c = 0; c < commandsToSend and !messagesPool.empty(); c++) {
			buffer += messagesPool.front();
//			LOG(LCDSpicer2::Logger::DEBUG, "Command:[" + messagesPool.front() + "]");
			messagesPool.pop();
		}

//		LOG(LCDSpicer2::Logger::DEBUG, "Command:[" + buffer + "]");

		if (not send(buffer))
			return STATUS_UNSTABLE;

		// Sleep.
		usleep(affinity);

		buffer.clear();
	}
	while (!messagesPool.empty());

	return STATUS_OK;
}

LCDSpicer2::Screen* LCDProc::createScreen(uint64_t seconds) {
	return new LCDProcScreen(seconds, &messagesPool, &fontSize, &screenSize);
}

void LCDProc::processAnswer(const string& data, const string& target) {

	size_t begin = 0, end = 0;

	while (true) {
		string answer;
		begin = data.find(target, begin + end);
		if (begin == string::npos)
			break;

		end = data.find('\n', begin);
		begin += target.size();

		if (end != string::npos)
			end -= begin;
		else
			// Invalid message, no line feed.
			break;

		answer = data.substr(begin, end);

		// Log Warnings.
		if (target == "huh? " and !answer.empty())
			LOG(LCDSpicer2::Logger::WARNING, answer);

		// Register keys strokes.
		if (target == "key ") {
			LOG(LCDSpicer2::Logger::DEBUG, "Key pressed " + answer);
			// Check if the key is valid.
			if (keymap.find(answer) != keymap.end())
				registerButtonEvent(keymap[answer]);
		}
	}
}

vector<LCDSpicer2::Widget*> LCDProc::getAvailableWidgets() {
	LCDSpicer2::Position pos(1,1);
	LCDSpicer2::Dimension dim(1,1);

	LCDProcTextWidget*	text	= new LCDProcTextWidget(pos, dim, 0, nullptr, nullptr, 0);
	LCDProcBarWidget*	bar		= new LCDProcBarWidget(pos, dim, 0, nullptr, &fontSize, &screenSize, 0);
	LCDProcClockWidget*	clock	= new LCDProcClockWidget(pos, dim, 0, nullptr, &screenSize, 0);

	vector<LCDSpicer2::Widget*> widgets = {text, bar, clock};
	return widgets;
}
