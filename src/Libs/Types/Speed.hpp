/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Speed.hpp
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

#ifndef SRC_LIBS_TYPES_SPEED_HPP_
#define SRC_LIBS_TYPES_SPEED_HPP_ 1

#include <cstdint>

namespace LCDSpicer2 {

/**
 * LCDSpicer2::Speed
 *
 * @todo variable speed.
 * Information needed to handle speed.
 */
struct Speed {

	/// Stop, not moving, 0 speed.
	static const uint8_t STOP;

	/// Full speed, moving as fast as possible.
	static const uint8_t FULL;

	/**
	 * Creates a new Speed.
	 *
	 * @param speed in percent.
	 */
	Speed(uint8_t speed = Speed::STOP);

	/**
	 * Checks if a speed is valid.
	 *
	 * @param speed a speed in percent.
	 * @return true if the speed is a valid speed.
	 */
	static bool isValid(uint8_t speed);

	/**
	 * Sets the speed.
	 *
	 * @param newSpeed
	 */
	Speed* setSpeed(uint8_t newSpeed);

	/**
	 * Returns the current speed.
	 *
	 * @return the speed in percent.
	 */
	uint8_t getSpeed() const;

protected:

	/// Stores the speed.
	uint8_t speed;
};

} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_TYPES_SPEED_HPP_ */
