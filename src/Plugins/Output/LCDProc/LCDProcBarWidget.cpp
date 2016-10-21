/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LCDProcBarWidget.cpp
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

#include "LCDProcBarWidget.hpp"

LCDProcBarWidget::LCDProcBarWidget(
	LCDSpicer2::Position& position,
	LCDSpicer2::Dimension& dimension,
	uint64_t ticks,
	queue<string>* const messagesPool,
	const LCDSpicer2::Dimension* const fontSize,
	const LCDSpicer2::Dimension* const screenSize,
	const uint screenId
) :
	fontSize(fontSize),
	LCDProcWidget(messagesPool, screenSize, screenId),
	LCDSpicer2::BarWidget(position, dimension, ticks) {
		left = "";
		right = "\n";
		len = 0;
	}

void LCDProcBarWidget::redraw() {

	if (coordinates.empty())
		generateLCDdElement();

	uint percent = getValue()->getUInt();
	if (not isValidPercentage(percent))
		percent = 0;

	messagesPool->push(toString(std::to_string((uint) ceil(percent * len / 100))));
}

void LCDProcBarWidget::generateLCDdElement() {

	string message;
	if (direction == Direction::LEFT_RIGHT or direction == Direction::RIGHT_LEFT) {
		message = "widget_add " + id + "hbar\n";
		len = width * fontSize->getWidth();
	}
	else {
		message = "widget_add " + id + "vbar\n";
		len = height * fontSize->getHeight();
	}
	messagesPool->push(message);
	coordinates = std::to_string(X) + " " + std::to_string(Y) + " ";
}

LCDSpicer2::Specification LCDProcBarWidget::getSpecification() {

	LCDSpicer2::Specification specification = LCDSpicer2::Widget::getSpecification();
	specification.allowedDataTypes = DATA_PERCENT;

	LCDSpicer2::Parameter direction;

	direction.name = "Orientation";
	direction.type = DATA_STRING;
	direction.values.push_back(LCDSpicer2::Direction::DIRECTIONS[LCDSpicer2::Direction::LEFT_RIGHT]);
	direction.values.push_back(LCDSpicer2::Direction::DIRECTIONS[LCDSpicer2::Direction::DOWN_UP]);
	specification.parameters.push_back(direction);

	return specification;
}
