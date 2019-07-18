/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Logger.cpp
 * @ingroup		general
 * @since		Oct 24, 2015
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


#include <syslog.h>

#include "Logger.hpp"

using namespace LCDSpicer2;

// static variables.
Logger*	Logger::instance = nullptr;
uint8_t Logger::level = NOLOG;
const char* Logger::identifier = PACKAGE_NAME;

Logger::Logger(int logLevel) {

	this->level = logLevel;

	if (not logLevel) {
		return;
	}

	int level = 0;
	for (uint8_t c = 0, b = 1; c < 8; c++, b <<= 1) {
		if (b & logLevel) {
			level |= LOG_MASK(getSysLogLevel(b));
		}
	}
	setlogmask(level);

	openlog(identifier, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_DAEMON);
}

Logger* Logger::getInstance() {
	return instance;
}

Logger* Logger::getInstance(int logLevel) {

	if (not instance) {
		instance = new Logger(logLevel);
	}
	else {
		syslog(LOG_NOTICE, "The logger is already created, the new parameters will be ignored, use getInstance() instead.");
	}

	return instance;
}

Logger::~Logger() {
	closelog();
}

uint8_t Logger::getSysLogLevel(int level) {

	switch(level) {

	case EMERGENCY:
		return LOG_EMERG;

	case ALERT:
		return LOG_ALERT;

	case CRITICAL:
		return LOG_CRIT;

	case ERROR:
		return LOG_ERR;

	case WARNING:
		return LOG_WARNING;

	case NOTICE:
		return LOG_NOTICE;

	case INFO:
		return LOG_INFO;

	case DEBUG:
		return LOG_DEBUG;
	}

	return NOLOG;
}

bool Logger::isLogging(uint8_t level) {
	return (Logger::level & level) != NOLOG;
}

void Logger::log(uint8_t level, const string& message) {
	if (isLogging(level)) {
		syslog(getSysLogLevel(level), "%s", message.c_str());
	}
}

void Logger::terminate() {
	delete instance;
	instance = nullptr;
}
