/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		TextWidget.cpp
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

#include "GenericFunctions.hpp"
#include "TextWidget.hpp"

using namespace LCDSpicer2;

TextWidget::TextWidget(
	Position& position,
	Dimension& dimension,
	uint64_t ticks
) :
Widget(position, dimension, ticks) {
	registerFunction("Alignment",	BIND(TextWidget::setAlignmentWrapper));
	registerFunction("Direction",	BIND(TextWidget::setDirectionWrapper));
	registerFunction("FontSize",	BIND(TextWidget::setFontSizeWrapper));
	registerFunction("Speed",		BIND(TextWidget::setSpeedWrapper));
	Speed::setSpeed(DEFAULT_TEXT_SPEED);
}

uint8_t TextWidget::getType() {
	return Widget::TEXT;
}

void TextWidget::setAlignmentWrapper(Value& value) {
	setAlignment(value.getUInt());
}

void TextWidget::setFontSizeWrapper(Value& value) {
	value.get(fontSize);
}

void TextWidget::setDirectionWrapper(Value& value) {
	setDirection(value.getInt());
}

void TextWidget::setSpeedWrapper(Value& value) {
	setSpeed(value.getInt());
}

void TextWidget::alignValue() {

	string value = getValue()->getString();
	uint32_t size = value.size();

	if (size > width) {

		// Nothing to do too small.
		if (height == 1) {
			strValue = value;
			lastSize = size;
			return;
		}

		string line;
		vector<string> parts = Explode(value, ' ');
		value.clear();
		for (string part : parts) {

			if (part.empty())
				continue;

			if (line.size() + 1 + part.size() >= width) {
				value += AlignText(line, alignment, width);
				line.clear();
			}

			if (not line.empty())
				line += " ";
			line += part;
		}
		strValue = value + AlignText(line, alignment, width);
		return;
	}

	// Same size.
	if (size == width) {
		strValue = value;
		return;
	}

	// Need alignment.
	if (size != lastSize) {
		lastSize = size;
		strValue = AlignText(value, alignment, width, &addLeft, &addRight);
		return;
	}

	// Same alignment than before or adjusted one.
	strValue = addLeft + value + addRight;
}

Specification TextWidget::getSpecification() {

	Specification specification = Widget::getSpecification();
	specification.allowedDataTypes = DATA_STRING | DATA_PERCENT | DATA_BOOLEAN;

	Parameter
		alignment,
		direction,
		speed;

	alignment.name = "Alignment";
	alignment.type = DATA_STRING;
	alignment.values.insert(alignment.values.end(), Alignment::ALIGNMENTS.begin(), Alignment::ALIGNMENTS.end());
	specification.parameters.push_back(alignment);

	direction.name = "Direction";
	direction.type = DATA_STRING;
	direction.values.insert(direction.values.end(), Direction::DIRECTIONS.begin(), Direction::DIRECTIONS.end());
	specification.parameters.push_back(direction);

	speed.name = "Scroll speed";
	speed.type = DATA_PERCENT;
	specification.parameters.push_back(speed);

	return specification;
}
