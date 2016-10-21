/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Logger.hpp
 * @ingroup		general
 * @since		Oct 24, 2015
 * @author		Patricio A. Rossi (MeduZa)
 *
 * @copyright	Copyright © 2015 - 2016 Patricio A. Rossi (MeduZa)
 *
 * @copyright	lcdspicer is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * @copyright	lcdspicer is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * @copyright	You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SRC_LIBS_LOGGER_HPP_
#define SRC_LIBS_LOGGER_HPP_

#include <string>
using std::string;

#include "config.h"

namespace LCDSpicer2 {

#define LOG(type, message) {			\
	if (logger->isLogging(type))		\
		logger->log(type, message);		\
	}
/**
 * Logger.
 *
 * Basic wrapper class to the system log.
 */
class Logger {

public:

	static constexpr uint8_t NOLOG		= 0;
	static constexpr uint8_t EMERGENCY	= 1;
	static constexpr uint8_t ALERT		= 2;
	static constexpr uint8_t CRITICAL	= 4;
	static constexpr uint8_t ERROR		= 8;
	static constexpr uint8_t WARNING	= 16;
	static constexpr uint8_t NOTICE		= 32;
	static constexpr uint8_t INFO		= 64;
	static constexpr uint8_t DEBUG		= 128;
	static constexpr uint8_t ALL		= (EMERGENCY | ALERT | CRITICAL | ERROR | WARNING | NOTICE | INFO | DEBUG);

	static Logger* getInstance();

	static Logger* getInstance(int logLevel);

	virtual ~Logger();

	/**
	 * Checks if the logger is logging an specific log level, useful to avoid the creation of not necessary logging text.
	 * @param level the level to check.
	 * @return true if the logger is logging that level.
	 */
	static bool isLogging(uint8_t level);

	/**
	 * The main log function to add log entries.
	 * @param msg_level
	 * @param[in] message
	 */
	static void log(uint8_t msg_level, const string& message);

	/**
	 * In case that the logger need to be destroyed.
	 */
	static void terminate();

private:

	Logger(int logLevel);

	static Logger *instance;

	static uint8_t level;

	static const char* identifier;

	static uint8_t getSysLogLevel(int level);

};

}

#endif /* SRC_LIBS_LOGGER_HPP_ */
