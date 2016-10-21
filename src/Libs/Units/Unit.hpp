/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Unit.hpp
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

#ifndef SRC_LIBS_UNITS_UNIT_HPP_
#define SRC_LIBS_UNITS_UNIT_HPP_ 1

#include <string>
using std::string;

#include <vector>
using std::vector;

// To handle unordered map.
#include <unordered_map>
#ifndef umap
	#define umap std::unordered_map
#endif

/// Auto reduction to the minimal.
#define AUTO -1

namespace LCDSpicer2 {

/**
 * LCDSpicer2::Unit
 *
 * Abstract class that decorates the value with unit of measurement and formating.
 */
class Unit {

public:

	/**
	 * Clean up
	 */
	virtual ~Unit() {};

	/**
	 * Returns the list of handled conversion units.
	 *
	 * @return an array of strings the index is the code.
	 */
	umap<string, string> getUnits();

	/**
	 * Returns the value converted and with the unit symbol.
	 *
	 * @param the value to convert from.
	 * @param newUnit the new unit to covert to.
	 * @param decimals number of desired decimal units (default 2)
	 * @return
	 */
	virtual string getString(const long double& value, int16_t newUnit, uint8_t decimals = 2);

	/**
	 * Returns the converted value with double representation.
	 *
	 * @param the value to convert from.
	 * @param newUnit
	 * @return
	 */
	virtual long double getDouble(const long double& value, int16_t& newUnit) = 0;

	/**
	 * Returns the converted value as integer (with the lost of precision).
	 *
	 * @param value the value to convert from.
	 * @param[out] newUnit the new unit to convert into, if automatic is send will be set with the new detected unit.
	 * @return the converted value.
	 */
	uint64_t getInteger(const long double& value, int16_t& newUnit);

	/**
	 * Checks if a unit is a valid unit of measurement.
	 *
	 * @param unit
	 * @return true of good, false instead.
	 */
	bool isValidUnit(uint8_t unit);

	/**
	 * Returns the current unit's symbol.
	 *
	 * @param unit The code.
	 * @return the Symbol.
	 */
	string getSymbol();

	/**
	 * Converts the code into the symbol.
	 * @note Automatic and NONE will return nothing.
	 *
	 * @param unit The code.
	 * @return the Symbol.
	 */
	string getSymbol(uint8_t unit);

	/**
	 * Setter for unit.
	 * Validates the unit, if not valid the default will be used.
	 *
	 * @param unit the new unit type.
	 */
	void setUnit(uint8_t unit);

protected:

	/// The original value unit of measure.
	uint8_t unit;

	/// Stores and array with the possible units as string.
	vector<string> units;

};

} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_UNITS_UNIT_HPP_ */
