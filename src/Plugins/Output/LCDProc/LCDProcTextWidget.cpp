/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LCDProcTextWidget.cpp
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

#include "LCDProcTextWidget.hpp"
#include <cmath>

void LCDProcTextWidget::redraw() {

	if (coordinates.empty())
		generateLCDdElement();

	alignValue();
	messagesPool->push(toString(strValue));
}

void LCDProcTextWidget::generateLCDdElement() {

	string message = "widget_add " + id + "scroller\n";
	string orientation = (height > 1 ? " v " :" m ");

	messagesPool->push(message);
	coordinates =
		std::to_string(X) + " " +
		std::to_string(Y) + " " +
		std::to_string(X - 1 + width) + " " +
		std::to_string(Y - 1 + height) + orientation +
		std::to_string(getSpeed()) + " ";
}

uint8_t LCDProcTextWidget::getSpeed() const {
	if (not speed)
		return 0;
	int s = std::ceil(speed * 8 / 100);
	return (s == 0 ? 1 : s);
}

string LCDProcTextWidget::toString(string value) {

	// Trailing space needed to avoid the beginning of the text touching the end.
	if (value.length() > width)
		left = "\" ";
	else
		left = "\"";

	return LCDProcWidget::toString(value);
}

LCDSpicer2::Specification LCDProcTextWidget::getSpecification() {

	LCDSpicer2::Specification specification = LCDSpicer2::TextWidget::getSpecification();

	for (auto& parameter : specification.parameters) {
		if (parameter.name == "Direction") {
			parameter.values.clear();
			parameter.values.push_back(Direction::DIRECTIONS[Direction::LEFT_RIGHT]);
		}
	}

	return specification;
}

