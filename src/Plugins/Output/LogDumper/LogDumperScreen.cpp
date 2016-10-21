/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LogDumperScreen.cpp
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
#include "LogDumperScreen.hpp"

uint LogDumperScreen::screensCount = 0;

LogDumperScreen::LogDumperScreen(uint64_t seconds) : LCDSpicer2::Screen(seconds) {
	logger = LCDSpicer2::Logger::getInstance();
	screensCount++;
	screenNumber = screensCount;
	LOG(DEBUG, "LogDumper Screen " + std::to_string(screenNumber) + " created");
}

LogDumperScreen::~LogDumperScreen() {
	screensCount--;
	LOG(DEBUG, "LogDumper Screen " + std::to_string(screenNumber) + " destroyed");
}


LCDSpicer2::Widget* LogDumperScreen::createWidget(parameter_t type, LCDSpicer2::Position& position, LCDSpicer2::Dimension& dimension, uint64_t ticks) {
	if (type == WIDGET_TEXT)
		return new LogDumperWidget(position, dimension, ticks);
	return nullptr;
}

void LogDumperScreen::redraw() {
	//LOG(DEBUG, "LogDumper Screen " + std::to_string(screenNumber) + " redraw");
}

void LogDumperScreen::turnOff() {
	LOG(DEBUG, "LogDumper Screen " + std::to_string(screenNumber) + " Off");
}

void LogDumperScreen::turnOn() {
	LOG(DEBUG, "LogDumper Screen " + std::to_string(screenNumber) + " On");
}
