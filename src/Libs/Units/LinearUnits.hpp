/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LinearUnits.hpp
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

#ifndef SRC_LIBS_UNITS_LINEARUNITS_HPP_
#define SRC_LIBS_UNITS_LINEARUNITS_HPP_

#include "Unit.hpp"

namespace LCDSpicer2 {

/**
 * LCDSpicer2::LinearUnits
 *
 * This class provides general functions for linear converters.
 */
class LinearUnits: public Unit {

public:

	long double getDouble(const long double& value, int16_t& newUnit);

protected:

	uint base = 1000;

};

} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_UNITS_LINEARUNITS_HPP_ */
