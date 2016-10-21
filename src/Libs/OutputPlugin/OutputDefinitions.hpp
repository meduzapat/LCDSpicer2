/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		OutputTypes.hpp
 * @ingroup		outputPlugins
 * @since		Mar 10, 2014
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

#ifndef SRC_LIBS_OUTPUTPLUGIN_OUTPUTDEFINITIONS_HPP_
#define SRC_LIBS_OUTPUTPLUGIN_OUTPUTDEFINITIONS_HPP_ 1

#include "Definitions.hpp"

// Output types
#include "Position.hpp"
#include "Dimension.hpp"

namespace LCDSpicer2 {

/// Check for the correct Percentage values.
#define isValidPercentage(percent) (percent >= 0 and percent <= 100)

/// The default scroll speed when the text is bigger than its space.
#define DEFAULT_TEXT_SPEED 50

/**
 * @defgroup buttons Buttons definitions.
 *
 * @todo finish this.
 * @{
 */
#define BUTTON_0		0
#define BUTTON_1		1
#define BUTTON_2		2
#define BUTTON_3		3
#define BUTTON_4		4
#define BUTTON_5		5
#define BUTTON_6		6
#define BUTTON_7		7
#define BUTTON_8		8
#define BUTTON_9		9
#define BUTTON_UP		10
#define BUTTON_DOWN		11
#define BUTTON_LEFT		12
#define BUTTON_RIGHT	13
#define BUTTON_ESC		14
#define BUTTON_ENTER	15
#define BUTTON_BACK		16
#define BUTTON_ON_OFF	17
/// Check if a button code is  correct.
#define isValidButton(button) (button >= BUTTON_0 and button <= BUTTON_ON_OFF)
/// @}

/**
 * Structure with the information needed to populate a parameter.
 */
struct Parameter {
	/// The parameter name to display to the user.
	string			name;
	/// The parameter type code.
	uint			type;
	/// the possible values.
	vector<string>	values;
};

/**
 * Structure with the information needed to populate a widget.
 */
struct Specification {

	/// Can be moved?
	Position			movable;
	/// Can be resized?
	Position			resizable;
	/// the size is used only if cannot be resized.
	Dimension			size;
	/// Minimum refresh allowed.
	uint64_t			minRefresh = 0;
	/// Bits for the allowed data types.
	uint64_t			allowedDataTypes = NONE;
	/// Possible parameters.
	vector<Parameter>	parameters;
};

}

#endif /* SRC_LIBS_OUTPUTPLUGIN_OUTPUTDEFINITIONS_HPP_ */
