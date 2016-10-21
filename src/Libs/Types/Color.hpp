/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Color.hpp
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
#ifndef SRC_LIBS_TYPES_COLOR_HPP_
#define SRC_LIBS_TYPES_COLOR_HPP_ 1

#include <string>
using std::string;

namespace LCDSpicer2 {

/**
 * LCDSpicer2::Color
 * Handle colors.
 *
 * @todo set a bit base.
 * @todo create base converted.
 * @todo store and return the color on the desired base.
 */
struct Color {

	/// Input from R G B separate values
	Color(
		uint8_t R = 0,
		uint8_t G = 0,
		uint8_t B = 0
	) :
		R(R),
		G(G),
		B(B) {}

	/// Any kind of number to R G B (not larger than 16777215 or 0xFFFFFF)
	Color(uint32_t color);

	/// Input from text (format \#FFFFFF; \#FFFFFF or just FFFFFF, also accept 3 values strings like \#FFF; and others
	Color(const string& color);

	/**
	 * Check for the correct values for single colors.
	 *
	 * @todo is using 8 bits only.
	 * @param color
	 * @return true if the color is a valid color element.
	 */
	static bool isValidElement(uint color);

	/**
	 * Checks for the correct numeric color value (decimal) max FFFFFF.
	 *
	 * @param color a number to be check if a valid color.
	 * @return true if color is a valid color.
	 */
	static bool isValid(uint color);

	/**
	 * Input from R G B values.
	 *
	 * @param newR
	 * @param newG
	 * @param newB
	 * @return self
	 */
	Color* setColor(uint8_t newR, uint8_t newG, uint8_t newB);

	/**
	 * Any kind of color using a number that represent R G B.
	 *
	 * @param newColor
	 * @return self
	 */
	Color* setColor(uint32_t newColor);

	/**
	 * Input from text.
	 *
	 * @param new_color
	 * @return self
	 */
	Color* setColor(string new_color);

	/**
	 * Returns the Blue element of the color.
	 *
	 * @return a number that reprenset the blue part of the RGB.
	 */
	uint8_t getB() const;

	/**
	 * Returns the Green element of the color.
	 *
	 * @return a number that reprenset the Green part of the RGB.
	 */
	uint8_t getG() const;

	/**
	 * Returns the Red element of the color.
	 *
	 * @return a number that reprenset the Red part of the RGB.
	 */
	uint8_t getR() const;

	/**
	 * Returns the RGB color.
	 *
	 * @return the numeric representation of a RGB color.
	 */
	uint32_t getColor() const;


	/**
	 * Returns the RGB color as string.
	 *
	 * @return the numeric representation of a RGB color as string.
	 */
	string getRGB() const;

protected:

	/// Red part 0 - 255 or 0x0 - 0xFF
	uint8_t R;

	/// Green part 0 - 255 or 0x0 - 0xFF
	uint8_t G;

	/// Blue part 0 - 255 or 0x0 - 0xFF
	uint8_t B;

};

} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_TYPES_COLOR_HPP_ */
