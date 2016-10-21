/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Direction.hpp
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
#ifndef SRC_LIBS_TYPES_DIRECTION_HPP_
#define SRC_LIBS_TYPES_DIRECTION_HPP_ 1

#include <string>
using std::string;

#include <array>
using std::array;

namespace LCDSpicer2 {

/**
 * LCDSpicer2::Direction
 *
 * Define the orientation, example left-right.
 */
struct Direction {

	/**
	 * @}
	 * @defgroup directions Directions.
	 *
	 * Defines a direction, example a movement or a writing direction.
	 * @{
	 */
	static constexpr uint8_t LEFT_RIGHT	= 0;
	static constexpr uint8_t RIGHT_LEFT	= 1;
	static constexpr uint8_t DOWN_UP	= 2;
	static constexpr uint8_t UP_DOWN	= 3;
	/// @}

	static const array<const char*, 4> DIRECTIONS;

	/**
	 * Creates a new Direction.
	 *
	 * @param Direction to use.
	 */
	Direction(uint8_t direction = LEFT_RIGHT);

	/**
	 * Checks if a direction code is valid.
	 *
	 * @param direction the direction code.
	 * @return true if the direction is valid.
	 */
	static bool isValid(uint8_t direction);

	/**
	 * Sets the new direction.
	 *
	 * @param newDirection if the direction is invalid will default to the default one.
	 * @return self
	 */
	Direction* setDirection(uint8_t newDirection);

	/**
	 * Returns the direction.
	 *
	 * @return
	 */
	uint8_t getDirection();

protected:

	/// Stores the direction.
	uint8_t direction;
};

} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_TYPES_DIRECTION_HPP_ */
