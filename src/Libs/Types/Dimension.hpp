/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Dimension.hpp
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
#ifndef SRC_LIBS_TYPES_DIMENSION_HPP_
#define SRC_LIBS_TYPES_DIMENSION_HPP_ 1

#include <cstdint>

namespace LCDSpicer2 {

/**
 * LCDSpicer2::Dimension
 * Stores 2D Sizes.
 *
 * The maximum width and height of an element.
 */
struct Dimension {

	/**
	 * Creates a new Dimension object.
	 *
	 * @param width
	 * @param height
	 */
	Dimension(uint32_t width = 1, uint32_t height = 1);

	/**
	 * Clean up.
	 */
	virtual ~Dimension() {}

	/**
	 * Returns the height.
	 *
	 * @return the height in units.
	 */
	uint32_t getHeight() const;

	/**
	 * Returns the width.
	 *
	 * @return the width in units.
	 */
	uint32_t getWidth() const;

	/**
	 * Sets the Height.
	 * @param height in units.
	 * @return a pointer to Dimension.
	 */
	Dimension* setHeight(uint32_t height);

	/**
	 * Sets the width.
	 *
	 * @param width in units.
	 * @return a pointer to Dimension.
	 */
	Dimension* setWidth(uint32_t width);

protected:

	/// The width in units.
	uint32_t width;

	/// The height in units.
	uint32_t height;

};

} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_TYPES_DIMENSION_HPP_ */
