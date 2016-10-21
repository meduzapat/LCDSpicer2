/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Color.cpp
 * @ingroup
 * @since		Apr 17, 2016
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
#include "Color.hpp"

using namespace LCDSpicer2;

Color::Color(uint32_t number) {
	setColor(number);
}

Color::Color(const string& color) {
	setColor(color);
}

bool Color::isValidElement(uint color) {
	return (color >= 0 and color <= 0xFF);
}

bool Color::isValid(uint color) {
	return (color >= 0x000000 and color <= 0xFFFFFF);
}

Color* Color::setColor(uint8_t newR, uint8_t newG, uint8_t newB) {
	R = newR;
	G = newG;
	B = newB;

	return this;
}

Color* Color::setColor(uint32_t newColor) {
	// reduce and store
	B = newColor & 0xFF;
	newColor>>= 8;
	G = newColor & 0xFF;
	newColor>>= 8;
	R = newColor & 0xFF;

	return this;
}

Color* Color::setColor(string newColor) {

	if (newColor.empty() or newColor.size() != 6)
		setColor(0,0,0);
	else
		setColor(std::stoul(newColor, nullptr, 16));

	return this;
}

uint8_t Color::getB() const {
	return B;
}

uint8_t Color::getG() const {
	return G;
}

uint8_t Color::getR() const {
	return R;
}

uint32_t Color::getColor() const {
	uint32_t number = 0;
	number |= R;
	number<<= 8;
	number | G;
	number<<= 8;
	number | B;
	return number;
}

string Color::getRGB() const {

	uint32_t color = getColor();

	if (not color)
		return "000000";

	std::string hex = "0123456789ABCDEF";
	string rgb;

	while (color > 0) {
		rgb = hex[color % 16] + rgb;
		color /= 16;
	}

	return rgb;
}
