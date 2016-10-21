/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Backlight.hpp
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

#ifndef SRC_LIBS_TYPES_BACKLIGHT_HPP_
#define SRC_LIBS_TYPES_BACKLIGHT_HPP_ 1

#include <string>
using std::string;

namespace LCDSpicer2 {

/**
 * LCDSpicer2::Backlight
 * The possible values for a backlight aware screen.
 */
struct Backlight {

	 /**
	 * @defgroup backlight Backlight states.
	 *
	 * The possible values for a backlight aware screen.
	 * @{
	 */
	/// Turns the back light off
	static constexpr uint8_t OFF	= 0;

	/// Turns the back light on
	static constexpr uint8_t ON		= 1;

	/// The back light will blink
	static constexpr uint8_t BLICK	= 2;

	/// Like blink but faster
	static constexpr uint8_t FLASH	= 3;
	/// @}

	static const string BACKLIGHTS[];

	/**
	 * Creates a new Backlight.
	 *
	 * @param backlight to use.
	 */
	Backlight(uint8_t backlight = ON);

	/**
	 * Checks for the correct backlight values.
	 *
	 * @param backlight the code to check.
	 * @return true if the code is a valid backlight code.
	 */
	static bool isValid(uint8_t backlight);

	/**
	 * Returns the backlight value.
	 *
	 * @return the backlight code.
	 */
	uint8_t getBacklight() const;

	/**
	 * Set the backlight code.
	 *
	 * @param backLight
	 * @return self
	 */
	Backlight* setBacklight(uint8_t backLight = ON);

private:

	/// The backlight value to store.
	uint8_t backlight = ON;
};

} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_TYPES_BACKLIGHT_HPP_ */
