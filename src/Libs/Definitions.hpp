/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Definitions.hpp
 * @ingroup		types
 * @since		Mar 7, 2014
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

#ifndef SRC_LIBS_DEFINITIONS_HPP_
#define SRC_LIBS_DEFINITIONS_HPP_ 1

// To handle unordered map.
#include <unordered_map>
#ifndef umap
	#define umap std::unordered_map
#endif

// To use vectors.
#include <vector>
using std::vector;

// To use strings.
#include <string>
using std::string;
using std::to_string;
using std::stoi;

// To handle errors.
#include "Error.hpp"

// To use Value
#include "Value.hpp"

namespace LCDSpicer2 {

/// The directory to store temporary data.
#define DEFAULT_TEMP_DIR "/tmp/LCDSpicer2"

/// The data document version is used to differentiate between different file formats.
#define DataDocumentVersion "2.1"

/// Alias for a byte.
#define byte_t uint8_t

/// Alias for an IDs type.
#define id_t uint16_t

/// Alias for a Parameters type.
#define parameter_t uint8_t

/// @}

/**
 * @defgroup dataTypes Widget data types
 *
 * The widget data types, provided by input plugins, consumed by widgets.
 * @{
 */
/// Defines a value with its contents can be true or false.
#define DATA_BOOLEAN	1
/// Defines a value with its contents are text.
#define DATA_STRING		2
/// Defines a value that represents the a percent.
#define DATA_PERCENT	4
/// Defines a value representing a date time.
#define DATA_DATE		8
/// Checks if the value is a valid data type.
#define isValidDataType(x) (x & (DATA_BOOLEAN | DATA_STRING | DATA_PERCENT | DATA_DATE))
/// @}

///  Defines when nothing is set.
#define NONE		0

/// Used to specify that the element will be resolved automatically.
#define AUTO		-1

}

#endif /* SRC_LIBS_DEFINITIONS_HPP_ */

