/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LCDProcWidget.cpp
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

#include "LCDProcWidget.hpp"

uint LCDProcWidget::widgetCounter = 1;

LCDProcWidget::LCDProcWidget(
			queue<string>* const messagesPool,
			const LCDSpicer2::Dimension* const screenSize,
			const uint screenId
		) :
		messagesPool(messagesPool),
		screenSize(screenSize) {
	// Generate widget elements.
	id = "s" + std::to_string(screenId) + " w" + std::to_string(widgetCounter++) + " ";
}

string LCDProcWidget::toString(string value) {
	return "widget_set " + id + coordinates + left + value + right;
}
