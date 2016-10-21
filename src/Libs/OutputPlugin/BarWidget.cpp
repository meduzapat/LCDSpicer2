/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		BarWidget.cpp
 * @ingroup		outputPlugins
 * @since		Nov 21, 2015
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

#include "BarWidget.hpp"

using namespace LCDSpicer2;

BarWidget::BarWidget(Position& position, Dimension& dimension, uint64_t ticks) :
	Widget(position, dimension, ticks) {
	registerFunction("Direction", BIND(BarWidget::setDirectionWrapper));
}

uint8_t BarWidget::getType() {
	return Widget::BAR;
}

void BarWidget::setDirectionWrapper(Value& value) {
	setDirection(value.getInt());
}


Specification BarWidget::getSpecification() {

	Specification specification = Widget::getSpecification();
	specification.allowedDataTypes = DATA_PERCENT;

	Parameter direction;

	direction.name = "Orientation";
	direction.type = DATA_STRING;
	direction.values.insert(direction.values.end(), Direction::DIRECTIONS.begin(), Direction::DIRECTIONS.end());
	specification.parameters.push_back(direction);

	return specification;
}
