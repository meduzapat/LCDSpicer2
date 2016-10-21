/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Unit.cpp
 * @ingroup		general
 * @since		Feb 9, 2016
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

#include "Unit.hpp"

using namespace LCDSpicer2;

void Unit::setUnit(uint8_t unit) {
	this->unit = isValidUnit(unit) ? unit : 1;
}

umap<string, string> Unit::getUnits() {
	umap<string, string> table;
	for (int c = 1; c < units.size(); c++)
		table.emplace(units[c], std::to_string(c));
	return table;
}

string Unit::getSymbol() {
	return units[unit];
}

string Unit::getSymbol(uint8_t unit) {
	if (isValidUnit(unit))
		return units[unit];
	return "";
}

bool Unit::isValidUnit(uint8_t unit) {
	return (unit >= 1 and unit <= units.size());
}

string Unit::getString(const long double& value, int16_t newUnit, uint8_t decimals) {

	string result;

	if (not isValidUnit(newUnit) and newUnit != AUTO)
		return std::to_string(value);

	if (value == 0)
		result = "0.00";
	else if (newUnit == unit)
		result = std::to_string(value);
	else
		result = std::to_string(getDouble(value, newUnit));

	if (newUnit > 1)
		result = result.substr(0, result.find('.') + decimals + 1);
	else
		// Avoid decimals on base types.
		result = result.substr(0, result.find('.'));

	result += units[newUnit];

	return result;
}

uint64_t Unit::getInteger(const long double& value, int16_t& newUnit) {

	uint64_t result = getDouble(value, newUnit);

	return result;
}
