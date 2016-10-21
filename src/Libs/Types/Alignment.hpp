/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Alignment.hpp
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
#ifndef SRC_LIBS_TYPES_ALIGNMENT_HPP_
#define SRC_LIBS_TYPES_ALIGNMENT_HPP_

#include <array>
using std::array;

#include <string>
using std::string;

namespace LCDSpicer2 {

/**
 * LCDSpicer2::Alignment.
 *
 * Used to handle alignment on widgets that support alignment, like text.
 */
struct Alignment {

	 /**
	 * @defgroup textAlignment Text Alignments.
	 * @{
	 */

	/// Aligns text to the left (default).
	static constexpr uint8_t LEFT	= 0;

	/// Aligns text to the right.
	static constexpr uint8_t RIGHT	= 1;

	/// Centers the text.
	static constexpr uint8_t CENTER	= 2;

	//static constexpr uint8_t JUSTIFY; (TODO IDEA maybe? how?)

	static const array<const char*, 3> ALIGNMENTS;

	/**
	 * Creates a new Alignment.
	 *
	 * @param alignment to use.
	 */
	Alignment(uint8_t alignment = LEFT);

	/// Check for the correct Alignment values.
	static const bool isValid(uint8_t alignment);

	/**
	 * Sets a new alignment.
	 *
	 * @param alignment The new alignment.
	 * @return self
	 */
	Alignment* setAlignment(uint8_t newAlignment);

	/**
	 * Returns the alignment.
	 *
	 * @return
	 */
	uint8_t getAlignment();

protected:

	/// Stores the alignment.
	uint8_t alignment;
};


} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_TYPES_ALIGNMENT_HPP_ */
