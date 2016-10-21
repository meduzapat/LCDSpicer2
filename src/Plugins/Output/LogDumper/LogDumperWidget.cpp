/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LogDumperWidget.cpp
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

#include "LogDumperWidget.hpp"

uint LogDumperWidget::widgetCount = 0;

LogDumperWidget::LogDumperWidget(Position& position, Dimension& dimension, uint64_t ticks) : TextWidget(position, dimension, ticks) {

	// Instantiate logger.
	logger = LCDSpicer2::Logger::getInstance();
	widgetCount++;
	widgetNumber = widgetCount;
	LOG(DEBUG, "Widget " + std::to_string(widgetNumber) + " created");

	// Register function calls.
	registerFunction("attribute1" , BIND(LogDumperWidget::updateLogDumperAttribute1));
	registerFunction("attribute2" , BIND(LogDumperWidget::updateLogDumperAttribute2));
	registerFunction("attribute3" , BIND(LogDumperWidget::updateLogDumperAttribute3));
}

LogDumperWidget::~LogDumperWidget() {
	widgetCount--;
	LOG(DEBUG, "Widget " + std::to_string(widgetNumber) + " destroyed");
}

void LogDumperWidget::updateLogDumperAttribute1(LCDSpicer2::Value& value) {
	LOG(DEBUG, "Widget " + std::to_string(widgetNumber) + " Attribute 1 updated to " + value.getString());
}

void LogDumperWidget::updateLogDumperAttribute2(LCDSpicer2::Value& value) {
	LOG(DEBUG, "Widget " + std::to_string(widgetNumber) + " Attribute 2 updated to " + value.getString());
}

void LogDumperWidget::updateLogDumperAttribute3(LCDSpicer2::Value& value) {
	LOG(DEBUG, "Widget " + std::to_string(widgetNumber) + " Attribute 3 updated to " + value.getString());
}

void LogDumperWidget::redraw() {
	LOG(DEBUG,
		"Widget "	+ std::to_string(widgetNumber)	+
		" X: "		+ std::to_string(X)				+
		" Y: "		+ std::to_string(Y)				+
		" Width: "	+ std::to_string(width)			+
		" Height: "	+ std::to_string(height)		+
		" Value: "	+ getValue().getString()
	);

}
