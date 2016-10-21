/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Value.hpp
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

#ifndef SRC_LIBS_TYPES_VALUE_HPP_
#define SRC_LIBS_TYPES_VALUE_HPP_ 1

#include <vector>
using std::vector;

#include <string>
using std::string;

namespace LCDSpicer2 {

/**
 * LCDSpicer2::Value
 * LCDSpicer multitype value class.
 *
 * This "value" can hold any valid LCDSpicer valid type.
 * Stores the value and cast it back to any other value type needed.
 * No weird clean up, casting or conversions between types are needed,
 */
class Value {

public:

	/**
	 * @defgroup types LCDSpicer2 auto types.
	 *
	 * This are the basic types LCDSpicer2 can handle.
	 * @{
	 */

	/// This code represent a non valid type, the raw pointer is a nullptr.
	static constexpr uint8_t INVALID	= 0;

	/// 32bits int (smaller than a pointer?).
	static constexpr uint8_t INT		= 1;

	/// 32bits unsigned int (smaller than a pointer?).
	static constexpr uint8_t UINT		= 2;

	/// 64bits int.
	static constexpr uint8_t LONG		= 3;

	/// 64bits unsigned int.
	static constexpr uint8_t ULONG		= 4;

	/// Text elements.
	static constexpr uint8_t STRING		= 5;

	/// Floating point numbers.
	static constexpr uint8_t DOUBLE		= 6;

	/// Very big floating point numbers.
	static constexpr uint8_t LDOUBLE	= 7;

	/// Binary data.
	static constexpr uint8_t BINARY		= 8;

	/// Time data.
	static constexpr uint8_t DATETIME	= 9;

	/// Use this type to pass null pointers to unknown types handled internally by the input/output plugin.
	/// NOTE: the creator is responsible for the deallocation of any allocated memory.
	static constexpr uint8_t UNKNOWN	= 10;
	/// @}

	/**
	 * Constructs an empty value.
	 */
	Value();

	/**
	 * Creates a new Value from another Value.
	 *
	 * @param value
	 */
	Value(const Value& value);

	/**
	 * Creates a new copy from other value by Assignment.
	 *
	 * @param value
	 * @return a clone of value
	 */
	Value& operator=(const Value& value);

	/**
	 * Move by assignment.
	 *
	 * @param value rval
	 * @return the value.
	 */
	Value& operator=(Value&& value);

	/**
	 * Compares two values for equity.
	 *
	 * @param value
	 * @return true if the value is equal.
	 */
	bool operator==(const Value& value) const;

	/**
	 * Compares two values for inequity.
	 *
	 * @param value
	 * @return true if the value is different.
	 */
	bool operator!=(const Value& value) const;

	/**
	 * Move Constructor.
	 * Creates a new Value moving the information from another value.
	 *
	 * @param value
	 */
	Value(Value&& value);

	/**
	 * Deletes the dynamic memory stored on data (if any).
	 */
	virtual ~Value();

	/**
	 * Checks if the type is valid.
	 *
	 * @param x the code to check.
	 * @return true if a valid type.
	 */
	static bool isValid(uint8_t x);

	/**
	 * Checks if the type is numeric.
	 *
	 * @param x the code to check.
	 * @return true if the type code represent a numeric value.
	 */
	static bool isNumeric(uint8_t x);

	/**
	 * Checks if the type is signed.
	 *
	 * @param x the code to check.
	 * @return true if the typo code is a signed numeric type.
	 */
	static bool isSigned(uint8_t x);

	/**
	 * Deletes the contents.
	 * NOTE this method ignores unknown types, unknown types need to be deleted where they got created.
	 */
	void unset();

	/**
	 * @{
	 * @name Setters to handle basic types.
	 */

	/**
	 * Set using a pointer to another Value.
	 * (same as copy)
	 *
	 * @param newValue
	 */
	void set(Value* newValue);

	/**
	 * Set using a reference to another Value
	 * (same as move)
	 *
	 * @param newValue
	 */
	void set(Value& newValue);

	/**
	 * Binary data from vector.
	 *
	 * @param newValue
	 */
	void set(vector<uint8_t>& newValue);

	/**
	 * Binary data, C style.
	 *
	 * @param newValue
	 * @param size
	 */
	void set(uint8_t* newValue, size_t size);

	/**
	 * Normal strings, to improve speed the newValue will be destroyed.
	 *
	 * @param newValue
	 */
	void set(string newValue);

	/**
	 * Strings, dynamic allocated.
	 *
	 * @param newValue
	 */
	void set(string* newValue);

	/**
	 * strings, C style, converts to string.
	 *
	 * @param newValue
	 */
	void set(const char* newValue);

	/**
	 * Anything that can fit into a integer.
	 *
	 * @param newValue
	 */
	void set(int32_t newValue);

	/**
	 * Anything that can fit into a unsigned integer.
	 *
	 * @param newValue
	 */
	void set(uint32_t newValue);

	/**
	 * Anything that can fit into a 64bits integer.
	 *
	 * @param newValue
	 */
	void set(int64_t newValue);

	/**
	 * Anything that can fit into a unsigned 64bits integer.
	 *
	 * @param newValue
	 */
	void set(uint64_t newValue);

	/**
	 * Anything that can fit into a double.
	 *
	 * @param newValue
	 */
	void set(double newValue);

	/**
	 * Anything that can fit into a unsigned double.
	 *
	 * @param newValue
	 */
	void set(long double newValue);

	/**
	 * A date time structure.
	 *
	 * @param newValue
	 */
	void set(tm* newValue);

	/**
	 * @}
	 * @name Getters to handle basic types and container.
	 * @{
	 */

	/**
	 * Gets the LCDSpicer type code for this value.
	 *
	 * @return
	 */
	uint8_t getType() const;


	/**
	 * Returns the Raw data null pointer containing the value.
	 *
	 * @return void*
	 */
	void* getRawData() const;

	/**
	 * Real numbers 32 bit.
	 *
	 * @return int
	 */
	int32_t getInt() const;

	/**
	 * Positive small numbers.
	 *
	 * @return unsigned int
	 */
	uint32_t getUInt() const;

	/**
	 * Real numbers.
	 *
	 * @return Long Long
	 */
	int64_t getLong() const;

	/**
	 * Positive numbers.
	 *
	 * @return unsigned long long
	 */
	uint64_t getUlong() const;

	/**
	 * Text.
	 *
	 * @return string type
	 */
	string getString() const;

	/**
	 * Decimal.
	 *
	 * @return double type
	 */
	double getDouble() const;

	/**
	 * Big Decimal.
	 *
	 * @return long double type
	 */
	long double getLongDouble() const;

	tm* getDateTime() const;

	/**
	 * Convert by reference.
	 *
	 * @param value
	 */
	void get(int32_t& value);

	/**
	 * Convert by reference.
	 *
	 * @param value
	 */
	void get(uint32_t& value);

	/**
	 * Convert by reference.
	 *
	 * @param value
	 */
	void get(int64_t& value);

	/**
	 * Convert by reference.
	 *
	 * @param value
	 */
	void get(uint64_t& value);

	/**
	 * Convert by reference.
	 *
	 * @param value
	 */
	void get(string& value);

	/**
	 * Convert by reference.
	 *
	 * @param value
	 */
	void get(double& value);

	/**
	 * Convert by reference.
	 *
	 * @param value
	 */
	void get(long double& value);

	/**
	 * Convert By reference to datetime.
	 *
	 * @param value
	 */
	void get(tm*& value);
	/// @}

	/**
	 * Returns the value footPrint.
	 * @return
	 */
	uint64_t getFootPrint() const;

protected:

	/// Pointer to the data.
	void* data = nullptr;

	/// Original data type.
	uint8_t	type = INVALID;

	/// A value footprint.
	uint64_t footPrint = 0;

	/**
	 * Resets the internal values.
	 * Anything not deallocated will be leaked.
	 */
	void reset();
};

} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_TYPES_VALUE_HPP_ */
