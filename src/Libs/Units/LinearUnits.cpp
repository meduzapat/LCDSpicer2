/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LinearUnits.cpp
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
#include "LinearUnits.hpp"

namespace LCDSpicer2 {

long double LinearUnits::getDouble(const long double& value, int16_t& newUnit) {

	if (not isValidUnit(newUnit) and newUnit != AUTO)
		return 0.00;

	long double result = value;

	if (newUnit == AUTO) {
		uint8_t tempUnit = unit;
		do {
			if (base > result) {
				newUnit = tempUnit;
				return result;
			}
			result /= base;
			tempUnit++;
		}
		while (true);
	}

	if (newUnit > unit)
		for (uint8_t c = unit; c < newUnit; c++)
			result /= base;
	else if (newUnit < unit)
		for (uint8_t c = newUnit; c < unit; c++)
			result *= base;

	return result;
}

} /* namespace LCDSpicer2 */
