/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Rotation.hpp
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
#ifndef SRC_LIBS_TYPES_ROTATION_HPP_
#define SRC_LIBS_TYPES_ROTATION_HPP_ 1

#include <string>
using std::string;

namespace LCDSpicer2 {

/**
 * LCDSpicer2 Rotation
 *
 * Defines how the next screen will be selected.
 */
struct Rotation {

	/**
	 * @defgroup rotation Available screen rotations.
	 * @{
	 */
	/// Stay always on the first screen.
	static constexpr uint8_t STAY		= 0;
	/// The next screen will be chose randomly.
	static constexpr uint8_t RANDOM		= 1;
	/// Will start on the first screen and when it arrives to the last, it will go back to the first screen.
	static constexpr uint8_t PINGPONG	= 2;
	/// Will start from the first screen, when it arrives to the last screen it will start over.
	static constexpr uint8_t CAROUSEL	= 3;
	///@}

	/// List of possible rotation in human readable format.
	static const string ROTATIONS[];

	/**
	 * Creates a new Rotation object.
	 *
	 * @param rotation
	 */
	Rotation(uint8_t rotation = STAY, bool forward = true);

	/**
	 * Verifies that the rotation is valid.
	 *
	 * @param n
	 * @return true if the rotation is valid rotation type.
	 */
	static bool isValid(uint8_t n);

	/**
	 * Returns the stored Rotation.
	 *
	 * @return the rotation value.
	 */
	uint8_t getRotation() const;

	/**
	 * Sets a new rotation, if the rotation is not valid STAY will be set.
	 *
	 * @param rotation the new rotation value.
	 * @return self
	 */
	Rotation* setRotation(uint8_t rotation);

	/**
	 * Returns if the rotation direction.
	 *
	 * @return true if moving forward.
	 */
	bool isForward() const;

	/**
	 * Sets the direction.
	 * @param forward
	 * @return self
	 */
	Rotation* setForward(bool forward = true);

private:

	/// Stores the rotation value.
	uint8_t rotation = STAY;

	/// Stores a flag to specify if will move forward or backwards when applies.
	bool forward = true;
};

} // namespace.

#endif /* SRC_LIBS_TYPES_ROTATION_HPP_ */
