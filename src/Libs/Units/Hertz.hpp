/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Hertz.hpp
 * @ingroup		general
 * @since		Feb 12, 2016
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

#ifndef SRC_LIBS_UNITS_HERTZ_HPP_
#define SRC_LIBS_UNITS_HERTZ_HPP_

#include "LinearUnits.hpp"

namespace LCDSpicer2 {

/**
 * @defgroup frequencyUnits Frequency in Hertz units.
 * @{
 */
#define UNIT_HERTZ		1
#define UNIT_KILOHERTZ	2
#define UNIT_MEGAHERTZ	3
#define UNIT_GIGAHERTZ	4
///@}

/**
 * LCDSpicer2::Hertz
 *
 * Class that converts between units of frequency.
 */
class Hertz: public LinearUnits {

public:

	Hertz(const uint8_t unit);

};

} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_UNITS_HERTZ_HPP_ */
