/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Value.cpp
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
#include "Value.hpp"
// To use time.
#include <ctime>

using namespace LCDSpicer2;

#define CHECK_NUMBERS							\
	case INT:									\
		return *static_cast<int32_t*>(data);	\
	case UINT:									\
		return *static_cast<uint32_t*>(data);	\
	case LONG:									\
		return *static_cast<int64_t*>(data);	\
	case ULONG:									\
		return *static_cast<uint64_t*>(data);	\
	case DOUBLE:								\
		return *static_cast<double*>(data);		\
	case LDOUBLE:								\
		return *static_cast<long double*>(data);\
	case DATETIME:								\
		return mktime(getDateTime());

Value::Value() {
	reset();
}

Value::Value(const Value& value) {

	switch (value.type) {

	case INT:		set(value.getInt());
		break;

	case UINT:		set(value.getUInt());
		break;

	case LONG:		set(value.getLong());
		break;

	case ULONG:		set(value.getUlong());
		break;

	case STRING:	set(value.getString());
		break;

	case DOUBLE:	set(value.getDouble());
		break;

	case LDOUBLE:	set(value.getLongDouble());
		break;

	case DATETIME:	set(value.getDateTime());
		break;
	}
}

Value& Value::operator=(const Value& value) {

	switch (value.type) {

	case INT:		set(value.getInt());
		break;

	case UINT:		set(value.getUInt());
		break;

	case LONG:		set(value.getLong());
		break;

	case ULONG:		set(value.getUlong());
		break;

	case STRING:	set(value.getString());
		break;

	case DOUBLE:	set(value.getDouble());
		break;

	case LDOUBLE:	set(value.getLongDouble());
		break;

	case DATETIME:	set(value.getDateTime());
		break;
//	case BINARY:	set(value.get());
//	break;
	}
	return *this;
}

Value& Value::operator=(Value&& value) {

	unset();
	type = std::move(value.type);
	data = std::move(value.data);
	footPrint = std::move(value.getFootPrint());
	value.reset();
//	value.data = nullptr;
//	value.type = Value::INVALID;
//	value.footPrint = 0;
	return *this;
}

bool Value::operator==(const Value& value) const {

	if (footPrint == value.footPrint)
		return true;

	return false;
}

bool Value::operator!=(const Value& value) const {
	return !(*this == value);
}

Value::Value(Value&& value) {

	unset();
	type = std::move(value.type);
	data = std::move(value.data);
	footPrint = std::move(value.getFootPrint());
	value.reset();
//	value.data = nullptr;
//	value.type = Value::INVALID;
//	value.footPrint = 0;
}

Value::~Value() {
	if (type == UNKNOWN and data != nullptr)
		return;
	unset();
}

bool Value::isValid(uint8_t x) {
	return (x <= UNKNOWN and x >= INT);
}

bool Value::isNumeric(uint8_t x) {
	return (x == UNKNOWN or x == BINARY or x == STRING or x == DATETIME ? false : true);
}

bool Value::isSigned(uint8_t x) {
	return (x == INT or x == LONG or x == DOUBLE or x == LDOUBLE);
}

void Value::unset() {

	if (data == nullptr) {
		reset();
		return;
	}

	switch (type) {

	case INVALID:
		return;

	case INT:
		delete static_cast<int32_t*>(data);
		break;

	case UINT:
		delete static_cast<uint32_t*>(data);
		break;

	case LONG:
		delete static_cast<int64_t*>(data);
		break;

	case ULONG:
		delete static_cast<uint64_t*>(data);
		break;

	case DOUBLE:
		delete static_cast<double*>(data);
		break;

	case LDOUBLE:
		delete static_cast<long double*>(data);
		break;

	case STRING:
		delete static_cast<string*>(data);
		break;

	case BINARY:
		delete static_cast<vector<uint8_t>*>(data);
		break;

	// Pointers and pointed data.
	case DATETIME:
	// Impossible to know how the pointer was created, the source of the data need to deallocate this memory.
	case UNKNOWN:
		break;
	}

	reset();
}

void Value::reset() {
	data = nullptr;
	type = INVALID;
	footPrint = 0;
}

/*
 * Setters
 */

void Value::set(Value* newValue) {

	unset();

	switch (newValue->type) {

	case INT:		set(newValue->getInt());
		break;

	case UINT:		set(newValue->getUInt());
		break;

	case LONG:		set(newValue->getLong());
		break;

	case ULONG:		set(newValue->getUlong());
		break;

	case STRING:	set(newValue->getString());
		break;

	case DOUBLE:	set(newValue->getDouble());
		break;

	case LDOUBLE:	set(newValue->getLongDouble());
		break;

	case DATETIME:	set(newValue->getDateTime());
		break;
	}
}

void Value::set(Value& newValue) {

	unset();
	type = std::move(newValue.type);
	data = std::move(newValue.data);
	footPrint = std::move(newValue.getFootPrint());
	newValue.reset();
//	newValue.data = nullptr;
//	newValue.type = Value::INVALID;
//	newValue.footPrint = 0;
}

void Value::set(vector<uint8_t>& newValue) {

	unset();
	data = new vector<uint8_t>(newValue);
	type = BINARY;
	for (uint8_t b : newValue)
		footPrint += b;
}

void Value::set(uint8_t* newValue, size_t size) {
	vector<uint8_t> temp(newValue, newValue + size);
	set(temp);
}

void Value::set(string newValue) {
	set(new string(std::move(newValue)));
}

void Value::set(const char* newValue) {
	set(new string(newValue));
}

void Value::set(string* newValue) {

	unset();
	data = newValue;
	type = STRING;
	// FIXME really bad implementation with a lot of possible crash but I need to finish this other time.
	for (uint c =0; c < newValue->size(); c++)
		footPrint += (newValue->at(c) + c);
}

void Value::set(int32_t newValue) {

	unset();
	data = new int32_t(newValue);
	type = INT;
	footPrint = newValue;
}

void Value::set(uint32_t newValue) {


	unset();
	data = new uint32_t(newValue);
	type = UINT;
	footPrint = newValue;
}

void Value::set(int64_t newValue) {

	unset();
	data = new int64_t(newValue);
	type = LONG;
	footPrint = newValue;
}

void Value::set(uint64_t newValue) {

	unset();
	data = new uint64_t(newValue);
	type = ULONG;
	footPrint = newValue;
}

void Value::set(double newValue) {

	unset();
	data = new double(newValue);
	type = DOUBLE;
	footPrint = newValue * 100;
}

void Value::set(long double newValue) {

	unset();
	data = new long double(newValue);
	type = LDOUBLE;
	footPrint = newValue;
}

void Value::set(std::tm* newValue) {

	unset();
	data = newValue;
	type = DATETIME;
	footPrint = mktime(newValue);
}

/*
 * Getters
 */

uint8_t Value::getType() const {
	return type;
}

void* Value::getRawData() const {
	return data;
}

int32_t Value::getInt() const {

	if (not data)
		return 0;

	switch (type) {

	CHECK_NUMBERS

	case STRING:
		try {
			return std::stoi(*static_cast<string*>(data));
		}
		catch (...) {}
	}

	return 0;
}

uint32_t Value::getUInt() const {

	if (not data)
		return 0;

	switch (type) {

	CHECK_NUMBERS

	case STRING:
		try {
			return std::stoul(*static_cast<string*>(data));
		}
		catch (...) {}
	}

	return 0;
}

int64_t Value::getLong() const {

	if (not data)
		return 0;

	switch (type) {

	CHECK_NUMBERS

	case STRING:
		try {
			return std::stoll(*static_cast<string*>(data));
		}
		catch (...) {}
	}

	return 0;
}

uint64_t Value::getUlong() const {

	if (not data)
		return 0;

	switch (type) {

	CHECK_NUMBERS

	case STRING:
		try {
			return std::stoull(*static_cast<string*>(data));
		}
		catch (...) {}
	}

	return 0;
}

string Value::getString() const {

	string temp;

	if (not data)
		return temp;

	switch (type) {

	case INT:
		temp = std::move(std::to_string(*static_cast<int32_t*>(data)));
		break;

	case UINT:
		temp = std::move(std::to_string(*static_cast<uint32_t*>(data)));
		break;

	case LONG:
		temp = std::move(std::to_string(*static_cast<int64_t*>(data)));
		break;

	case ULONG:
		temp = std::move(std::to_string(*static_cast<uint64_t*>(data)));
		break;

	case DOUBLE:
		temp = std::move(std::to_string(*static_cast<double*>(data)));
		break;

	case LDOUBLE:
		temp = std::move(std::to_string(*static_cast<long double*>(data)));
		break;

	case STRING:
		temp = *static_cast<string*>(data);
		break;

	// crazy but possible.
	case BINARY:
		for (auto value : *static_cast<vector<uint8_t>*>(data))
			temp.append(std::to_string(value));
		break;

	case DATETIME:
		char buffer[80];
		std::strftime(buffer, 80, "%c", getDateTime());
		temp = buffer;
		break;
	}

	return temp;
}

double Value::getDouble() const {

	switch (type) {

	CHECK_NUMBERS

	case STRING:
		try {
			return std::stod(*static_cast<string*>(data));
		}
		catch (...) {}
	}
	return 0.00;
}

long double Value::getLongDouble() const {

	switch (type) {

	CHECK_NUMBERS

	case STRING:
		try {
			return std::stold(*static_cast<string*>(data));
		}
		catch (...) {}
	}
	return 0.00;
}

std::tm* Value::getDateTime() const {

	if (type == DATETIME)
		return static_cast<std::tm*>(data);

	std::time_t rawtime = getInt();
	return std::localtime(&rawtime);
}

void Value::get(int32_t& value) {
	value = getInt();
}

void Value::get(uint32_t& value) {
	value = getUInt();
}

void Value::get(int64_t& value) {
	value = getLong();
}

void Value::get(uint64_t& value) {
	value = getUlong();
}

void Value::get(string& value) {
	value = getString();
}

void Value::get(double& value) {
	value = getDouble();
}

void Value::get(long double& value) {
	value = getLongDouble();
}

void Value::get(std::tm*& value) {
	value = getDateTime();
}

uint64_t Value::getFootPrint() const {
	return footPrint;
}
