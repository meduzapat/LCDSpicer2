/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LogDumperScreen.hpp
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
#ifndef SRC_PLUGINS_OUTPUT_LOGDUMPER_LOGDUMPERSCREEN_HPP_
#define SRC_PLUGINS_OUTPUT_LOGDUMPER_LOGDUMPERSCREEN_HPP_

#include "LogDumperWidget.hpp"
#include "Logger.hpp"
#include "Screen.hpp"

/**
 * LogDumperScreen.
 *
 * A screen a does nothing.
 */
class LogDumperScreen: public LCDSpicer2::Screen {

public:

	LogDumperScreen(uint64_t seconds);

	virtual ~LogDumperScreen();

	void redraw();

protected:

	uint screenNumber = 0;

	static uint screensCount;

	LCDSpicer2::Logger* logger = nullptr;

	LCDSpicer2::Widget* createWidget(parameter_t type, LCDSpicer2::Position& position, LCDSpicer2::Dimension& dimension, uint64_t ticks);

	void turnOff();

	void turnOn();
};

#endif /* SRC_PLUGINS_OUTPUT_LOGDUMPER_LOGDUMPERSCREEN_HPP_ */
