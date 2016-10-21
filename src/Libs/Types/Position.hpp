/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Position.hpp
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
#ifndef SRC_LIBS_TYPES_POSITION_HPP_
#define SRC_LIBS_TYPES_POSITION_HPP_ 1

#include <cstdint>

namespace LCDSpicer2 {

/**
 * LCDSpicer2::Position
 * Stores 2D positions.
 *
 * Basic X and Y coordinates.
 */
struct Position {

	/**
	 * Creates a new position.
	 * @param X
	 * @param Y
	 */
	Position(uint32_t X = 0, uint32_t Y = 0);

	/**
	 * Clean up.
	 */
	virtual ~Position() {}

	/**
	 * Returns the coordinate X in units.
	 *
	 * @return
	 */
	uint32_t getX() const;

	/**
	 * Returns the coordinate Y in units.
	 *
	 * @return
	 */
	uint32_t getY() const;

	/**
	 * Sets the Height.
	 * @param X in units.
	 * @return a pointer to Dimension.
	 */
	Position* setX(uint32_t X);

	/**
	 * Sets the width.
	 *
	 * @param Y in units.
	 * @return a pointer to Dimension.
	 */
	Position* setY(uint32_t Y);

protected:

	/// Number of units from 1.
	uint32_t X;

	/// Number of units from 1.
	uint32_t Y;

};

} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_TYPES_POSITION_HPP_ */
