/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Widget.cpp
 * @ingroup		outputPlugins
 * @since		Nov 11, 2015
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

#include "Widget.hpp"

using namespace LCDSpicer2;

const array<const char*, 6> Widget::WIDGETS = {
	"Text",
	"Progress Bar",
	"Icon",
	"Bitmap",
	"Chart",
	"Clock"
};

Widget::~Widget() {
	if (final and value != nullptr)
		delete value;
}

bool Widget::isValid(uint8_t widget) {
	return (widget >= Widget::TEXT and widget <= Widget::CLOCK);
}

void Widget::updateAttribute(const string& attributeName, Value& value) {
	if (functions.find(attributeName) != functions.end())
		functions[attributeName](value);
	dirty = true;
}

void Widget::registerFunction(string name, std::function<void(Value&)> function) {
	functions.insert({std::move(name), function});
}

void Widget::setValue(Value* const value) {

	if (this->value != nullptr)
		this->value->unset();

	this->value = value;
	lastValueFootPrint = value->getFootPrint();
	dirty = true;
}

Value* const Widget::getValue() {
	return value;
}

void Widget::refresh() {

	if (lastValueFootPrint != value->getFootPrint())
		dirty = true;

	if (not dirty)
		return;

	redraw();
	dirty = false;
	lastValueFootPrint = value->getFootPrint();
	mark();
}

void Widget::setFinal() {
	changeInterval(0);
	final = true;
}

bool Widget::isFinal() {
	return final;
}

bool Widget::isDirty() {
	return dirty;
}

void Widget::setDirty() {
	dirty = true;
}

Specification Widget::getSpecification() {

	Specification specification;

	specification.movable.setX(true)->setY(true);
	specification.resizable.setX(true)->setY(true);
	specification.size.setWidth(0)->setHeight(0);
	specification.allowedDataTypes = NONE;

	return specification;
}
