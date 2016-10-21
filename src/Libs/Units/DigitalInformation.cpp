/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		DigitalInformation.cpp
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

#include "DigitalInformation.hpp"

using namespace LCDSpicer2;

DigitalInformation::DigitalInformation(const uint8_t unit) {

	units = {
		"",		// NONE
		"B",	// Byte
		"KB",	// kibibyte
		"MB",	// mebibyte
		"GB",	// gibibyte
		"TB",	// tebibyte
		"PB",	// pebibyte
	};
	base = 1024;
	setUnit(unit);
}

uint64_t DigitalInformation::getInteger(const long double& value, uint8_t newUnit) {

	if (not isValidUnit(newUnit) and newUnit != AUTO)
		return 0;

	uint64_t result = (uint64_t) value;

	if (newUnit == AUTO) {
		uint8_t tempUnit = unit;
		do {
			if (base > result) {
				newUnit = tempUnit;
				return result;
			}
			result >>= 10;
			tempUnit++;
		}
		while (true);
	}

	if (newUnit > unit)
		result = result >> (newUnit - unit) * 10;
	else if (newUnit < unit)
		result = result << (unit - newUnit) * 10;

	return result;
}
