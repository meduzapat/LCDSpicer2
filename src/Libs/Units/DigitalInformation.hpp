/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		DigitalInformation.hpp
 * @ingroup		general
 * @since		Feb 10, 2016
 * @author		Patricio A. Rossi (MeduZa)
 *
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

#ifndef SRC_LIBS_UNITS_DIGITALINFORMATION_HPP_
#define SRC_LIBS_UNITS_DIGITALINFORMATION_HPP_ 1

#include "LinearUnits.hpp"

namespace LCDSpicer2 {

/**
 * @defgroup digitalInformation Digital information units.
 * @{
 */
#define UNIT_BYTE		1
#define UNIT_KIBIBYTE	2
#define UNIT_MEBIBYTE	3
#define UNIT_GIBIBYTE	4
#define UNIT_TEBIBYTE	5
#define UNIT_PEBIBYTE	6
///@}

/**
 * LCDSpicer2::DigitalInformation
 *
 * Class that handles units of digital information in binary size (1024).
 */
class DigitalInformation: public LinearUnits {

public:

	DigitalInformation(const uint8_t unit);

	uint64_t getInteger(const long double& value, uint8_t newUnit);

};

} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_UNITS_DIGITALINFORMATION_HPP_ */
