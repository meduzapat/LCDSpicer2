/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LCDProcScreen.hpp
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

#ifndef SRC_PLUGINS_OUTPUT_LCDPROC_LCDPROCSCREEN_HPP_
#define SRC_PLUGINS_OUTPUT_LCDPROC_LCDPROCSCREEN_HPP_ 1

#include <queue>
using std::queue;

#include "LCDProcTextWidget.hpp"
#include "LCDProcBarWidget.hpp"
#include "LCDProcClockWidget.hpp"
#include "Logger.hpp"
#include "Screen.hpp"
using LCDSpicer2::Specification;

/**
 * LogDumperScreen.
 *
 * A screen a does nothing.
 */
class LCDProcScreen : public LCDSpicer2::Screen {

public:

	/**
	 * Creates a new Screen.
	 *
	 * @param seconds The number of seconds this screen need to be displayed.
	 * @param messagesPool Stores the messages to send to LCDd.
	 * @param screenSize The screen size on the device.
	 */
	LCDProcScreen(
		const uint64_t seconds,
		queue<string>* const messagesPool,
		const LCDSpicer2::Dimension* const fontSize,
		const LCDSpicer2::Dimension* const screenSize
	);

	/**
	 * LCDProc redraws for us.
	 */
	void redraw() {}

	umap<id_t, Specification> getSpecifications();

protected:

	/// The message pool to send messages to the LCDd server.
	queue<string>* messagesPool;

	/// The FontSize.
	const LCDSpicer2::Dimension* fontSize;

	/// The display size.
	const LCDSpicer2::Dimension* screenSize;

	LCDSpicer2::Widget* createWidget(
		parameter_t type,
		LCDSpicer2::Position& position,
		LCDSpicer2::Dimension& dimension,
		uint64_t ticks
	);

	void turnOff();

	void turnOn();

private:

	static uint screenCounter;

	/// Pre build string to avoid recreation
	string changeCall = "";

	/// LCDd's Screen name
	uint screenName = 0;
};

#endif /* SRC_PLUGINS_OUTPUT_LCDPROC_LCDPROCSCREEN_HPP_ */
