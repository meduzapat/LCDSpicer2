/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LogDumperWidget.hpp
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
#ifndef SRC_PLUGINS_OUTPUT_LOGDUMPER_LOGDUMPERWIDGET_HPP_
#define SRC_PLUGINS_OUTPUT_LOGDUMPER_LOGDUMPERWIDGET_HPP_ 1

#include "TextWidget.hpp"

/**
 * LogDumperWidget.
 *
 * The only Widget the LogDumper plugin provide, is a text widget.
 */
class LogDumperWidget : public LCDSpicer2::TextWidget {

public:

	LogDumperWidget(Position& position, Dimension& dimension, uint64_t ticks);

	virtual ~LogDumperWidget();

	void updateLogDumperAttribute1(LCDSpicer2::Value& value);

	void updateLogDumperAttribute2(LCDSpicer2::Value& value);

	void updateLogDumperAttribute3(LCDSpicer2::Value& value);

	void redraw();

protected:

	uint widgetNumber = 0;

	static uint widgetCount;

	LCDSpicer2::Logger* logger = nullptr;

};

#endif /* SRC_PLUGINS_OUTPUT_LOGDUMPER_LOGDUMPERWIDGET_HPP_ */
