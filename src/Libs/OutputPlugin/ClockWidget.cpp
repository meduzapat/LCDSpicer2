/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		ClockWidget.cpp
 * @ingroup		outputPlugins
 * @since		Feb 18, 2016
 * @author		Patricio A. Rossi (MeduZa)
 * @copyright	Copyright © 2015 Patricio A. Rossi (MeduZa)
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

#include "ClockWidget.hpp"

using namespace LCDSpicer2;

const array<const char*, 3> ClockWidget::SIZES = {
	"Small",
	"Medium",
	"Large"
};

const array<const char*, 2> ClockWidget::FORMATS = {
	"12hrs",
	"24hrs"
};

ClockWidget::ClockWidget(
	Position& position,
	Dimension& dimension,
	uint64_t ticks
) :
Widget(position, dimension, ticks) {
	registerFunction("Size",			BIND(ClockWidget::setSizeWrapper));
	registerFunction("Format",			BIND(ClockWidget::setFormatWrapper));
	registerFunction("Seconds",			BIND(ClockWidget::setSecondsWrapper));
	registerFunction("LeadingZeroes",	BIND(ClockWidget::setLeadingZeroesWrapper));
}

uint8_t ClockWidget::getType() {
	return Widget::CLOCK;
}

void ClockWidget::setSizeWrapper(Value value) {
	size = value.getUInt();
}

void ClockWidget::setFormatWrapper(Value value) {
	timeFormat = value.getInt();
}

void ClockWidget::setSecondsWrapper(Value value) {
	seconds = value.getInt() == true;
}

void ClockWidget::setLeadingZeroesWrapper(Value value) {
	leadingZeroes = value.getInt() == true;
}

Specification ClockWidget::getSpecification() {

	Specification specification = Widget::getSpecification();
	specification.allowedDataTypes = DATA_DATE;

	Parameter
		size,
		timeFormat,
		seconds,
		leadingZeroes;

	size.name = "Clock Size";
	size.type = DATA_STRING;
	size.values.insert(size.values.end(), SIZES.begin(), SIZES.end());
	specification.parameters.push_back(size);

	timeFormat.name = "Clock format";
	timeFormat.type = DATA_STRING;
	timeFormat.values.insert(timeFormat.values.end(), FORMATS.begin(), FORMATS.end());
	specification.parameters.push_back(timeFormat);

	seconds.name = "Display seconds";
	seconds.type = DATA_BOOLEAN;
	specification.parameters.push_back(seconds);

	leadingZeroes.name = "Display leading zeroes";
	leadingZeroes.type = DATA_BOOLEAN;
	specification.parameters.push_back(leadingZeroes);

	return specification;
}
