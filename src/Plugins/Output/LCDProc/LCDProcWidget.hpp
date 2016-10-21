/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LCDProcWidget.hpp
 * @ingroup		LCDProcOutputPlugin
 * @since		jan 17, 2016
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

#ifndef SRC_PLUGINS_OUTPUT_LCDPROC_LCDPROCWIDGET_HPP_
#define SRC_PLUGINS_OUTPUT_LCDPROC_LCDPROCWIDGET_HPP_ 1

#include <string>
using std::string;

#include <queue>
using std::queue;

// For Ceil and floor.
#include <cmath>

#include "OutputDefinitions.hpp"

/**
 * LCDProcWidget.
 *
 * Basic widget functionality for LCDProc.
 */
class LCDProcWidget {

public:

	/**
	 * General Functionality for every LCDProc widget.
	 *
	 * @param messagesPool
	 * @param screenSize
	 * @param screenId
	 */
	LCDProcWidget(
		queue<string>* const messagesPool,
		const LCDSpicer2::Dimension* const screenSize,
		const uint screenId
	);

	virtual ~LCDProcWidget() {}

protected:

	/// The LCDd screen and id.
	string	id,
	/// Coordinates for this element.
			coordinates,
	/// Anything that need to be added to the right of the value.
			left = "\"",
	/// Anything that need to be added to the left of the value.
			right = "\"\n";

	/// The message pool to send messages to the LCDd server.
	queue<string>* const messagesPool;

	/// The screen size,
	const LCDSpicer2::Dimension* const screenSize;

	/**
	 * Convert the widget elements into LCDd command.
	 * @return
	 */
	string toString(string value);

	/**
	 * Method to create the element on LCDd server.
	 */
	virtual void generateLCDdElement() = 0;

private:

	/// Keeps track of the numbers of widget, used as unique ID.
	static uint widgetCounter;
};

#endif /* SRC_PLUGINS_OUTPUT_LCDPROC_LCDPROCWIDGET_HPP_ */
