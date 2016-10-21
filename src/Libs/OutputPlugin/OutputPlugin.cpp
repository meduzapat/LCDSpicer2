/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		OutputPlugin.cpp
 * @ingroup		outputPlugins
 * @since		Dec 18, 2013
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

#include "OutputPlugin.hpp"

using namespace LCDSpicer2;

OutputPlugin::~OutputPlugin() {
	for(auto screen : screens)
		delete screen.second;
}

Screen* OutputPlugin::addScreen(id_t id, uint64_t seconds) {
	Screen* screen = createScreen(seconds);
	screens.insert({id, screen});
	return screen;
}

void OutputPlugin::toggleScreen(id_t screenId) {
	Screen* screen = screens.find(screenId)->second;

	if (activeScreen and activeScreen != screen)
		activeScreen->toggleScreen();

	activeScreen = screen;
	activeScreen->toggleScreen();
	activeScreen->mark();
}

Screen* OutputPlugin::getScreen(id_t screenId) {
	return screens[screenId];
}

Screen* OutputPlugin::getActiveScreen() {
	return activeScreen;
}

const vector<id_t> OutputPlugin::getScreenIds() const {
	vector<id_t> ids;
	for (auto it = screens.begin(); it != screens.end(); ++it) {
		ids.push_back(it->first);
	}
	ids.shrink_to_fit();
	return std::move(ids);
}

void OutputPlugin::setButtonsPool(queue<uint8_t>* pool) {
	this->buttonsPool = pool;
}

void OutputPlugin::registerButtonEvent(id_t buttonCode) {
	if (isValidButton(buttonCode))
		buttonsPool->push(buttonCode);
}
