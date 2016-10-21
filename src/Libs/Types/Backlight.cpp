/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Backlight.cpp
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
#include "Backlight.hpp"

using namespace LCDSpicer2;

const string BACKLIGHTS[] = {
	"Off",
	"On",
	"Blick",
	"Flash"
};

Backlight::Backlight(uint8_t backlight) {
	setBacklight(backlight);
}

bool Backlight::isValid(uint8_t backlight) {
	return (backlight >= OFF and backlight <= FLASH);
}

uint8_t Backlight::getBacklight() const {
	return backlight;
}

Backlight* Backlight::setBacklight(uint8_t backLight) {
	this->backlight = backLight;
	return this;
}
