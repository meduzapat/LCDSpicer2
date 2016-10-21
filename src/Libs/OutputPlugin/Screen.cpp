/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Screen.cpp
 * @ingroup		outputPlugins
 * @since		Oct 31, 2015
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

#include "Screen.hpp"

using namespace LCDSpicer2;

Screen::~Screen() {
	for (auto widget : widgets)
		delete widget.second;
}

void Screen::update(const string& attributeName, Value& value) {
	if (functions.find(attributeName) != functions.end()) {
		functions[attributeName](value);
		dirty = true;
	}
}

void Screen::registerFunction(string name, std::function<void (Value&)> function) {
	functions.insert({std::move(name), function});
}

Widget* Screen::addWidget(id_t id, parameter_t type, Position& position, Dimension& dimension, uint64_t ticks) {
	Widget* widget = createWidget(type, position, dimension, ticks);
	if (not widget)
		return nullptr;
	widgets[id] = widget;
	return widget;
}

const vector<id_t> Screen::getWidgetIds() const {
	vector<id_t> widgetIds;
	for (auto widget : widgets)
		widgetIds.push_back(widget.first);

	widgetIds.shrink_to_fit();
	return std::move(widgetIds);
}

void Screen::toggleScreen() {

	if (displaying) {
		turnOff();
		displaying = false;
	}
	else {
		displaying = true;
		turnOn();
	}

	for (auto widget : widgets)
		widget.second->setDirty();

	dirty = true;
}

void Screen::refresh() {

	if (not displaying)
		return;

	for (auto& widget : widgets) {
		widget.second->refresh();
	}

	redraw();
	dirty = false;
}

bool Screen::isDirty() {
	return dirty;
}

void Screen::setDirty() {
	dirty = true;
}
