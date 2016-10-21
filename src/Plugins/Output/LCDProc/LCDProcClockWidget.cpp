/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LCDProcClockWidget.cpp
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

#include "LCDProcClockWidget.hpp"

void LCDProcClockWidget::redraw() {

	if (coordinates.empty())
		generateLCDdElement();

	tm* timeinfo = getValue()->getDateTime();
	char buffer[10];
	std::strftime(buffer, 10, format.c_str(), timeinfo);

	for (uint c = 0; c < digits; c++) {
		if (buffer[c] == '0' and not leadingZeroes and (c == 0 or c == 2 or c == 4))
			buffer[c] = ' ';
		if (lastRead[c] != buffer[c]) {
			messagesPool->push(convertToValue(c, buffer[c]));
			lastRead[c] = buffer[c];
		}
	}

	if (seconds) {
		if ((timeinfo->tm_sec % 2) == 0)
			messagesPool->push(convertToValue(6, ' '));
		else
			messagesPool->push(convertToValue(6, ':'));
	}

	if (timeFormat) {
		std::strftime(buffer, 10, "%p", timeinfo);
		if (lastAP != buffer)
			messagesPool->push(clockAMPM + buffer + "\n");
		lastAP = buffer;
	}
}

void LCDProcClockWidget::generateLCDdElement() {

	id.pop_back();

	// LCDProc only have 1 clock, and the size is escalated based on the screen size.
	size = MEDIUM;

	if (timeFormat)
		format = "%I%M";
	else
		format = "%H%M";

	if (seconds) {
		digits = 6;
		format += "%S";
	}

	lastRead.resize(digits);

	for (int c = 0; c < digits; c++)
		messagesPool->push("widget_add " + id + "s" + std::to_string(c) + " num\n");

	if (timeFormat) {
		int pos = X + positions[digits - 1] + 2;

		messagesPool->push("widget_add " + id + "sAP string\n");
		clockAMPM = "widget_set " + id + "sAP " + std::to_string(pos) + " 1 ";
	}

	coordinates = "true";
	messagesPool->push("widget_add " + id + "s" + std::to_string(6) + " num\n");
	messagesPool->push(convertToValue(6, ':'));

	if (seconds) {
		messagesPool->push("widget_add " + id + "s" + std::to_string(7) + " num\n");
		messagesPool->push(convertToValue(7, ':'));
	}
}

string LCDProcClockWidget::convertToValue(uint position, char digit) {

	if (digit == ':')
		return "widget_set " + id + "s" + std::to_string(position) + " " + std::to_string(X + positions[position]) + " 10\n";

	if (digit == ' ')
		return "widget_set " + id + "s" + std::to_string(position) + " " + std::to_string(X + positions[position]) + " 11\n";

	return "widget_set " + id + "s" + std::to_string(position) + " " + std::to_string(X + positions[position]) + " " + digit + "\n";
}

LCDSpicer2::Specification LCDProcClockWidget::getSpecification() {

	LCDSpicer2::Specification specification = LCDSpicer2::ClockWidget::getSpecification();

	specification.resizable.setX(false)->setY(false);
	specification.movable.setX(true)->setY(false);
	uint h;
	if (screenSize->getHeight() < 4)
		h = 2;
	else
		h = 4;
	specification.size.setWidth(18)->setHeight(h);

	LCDSpicer2::Parameter theme;
	theme.name = "Clock Size";
	theme.type = NONE;

	return specification;
}
