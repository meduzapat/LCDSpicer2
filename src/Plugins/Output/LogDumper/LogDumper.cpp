/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LogDumper.cpp
 * @ingroup		logDumperOutputPlugin
 * @since		Nov 20, 2015
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

#include "LogDumper.hpp"

// Plugin factory functions.
#ifdef outputPluginFactory
	outputPluginFactory(LogDumper)
#else
	#error "Plugin factory function missing."
#endif

LogDumper::~LogDumper() {
	LOG(DEBUG, "LogDumper Destroyed");
}

bool LogDumper::initialize() {
	LOG(DEBUG, "LogDumper Created");
	return STATUS_OK;
}

uint8_t LogDumper::refresh() {
	activeScreen->refresh();
	return STATUS_OK;
}

LCDSpicer2::Screen* LogDumper::createScreen(uint64_t seconds) {
	return new LogDumperScreen(seconds);
}
