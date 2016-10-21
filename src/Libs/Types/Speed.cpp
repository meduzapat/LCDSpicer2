/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Speed.cpp
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
#include "Speed.hpp"

using namespace LCDSpicer2;

const uint8_t Speed::STOP	= 0;
const uint8_t Speed::FULL	= 100;

LCDSpicer2::Speed::Speed(uint8_t speed) {
	setSpeed(speed);
}

bool Speed::isValid(uint8_t speed) {
	return (speed >= 0 and speed <= 100);
}

Speed* LCDSpicer2::Speed::setSpeed(uint8_t newSpeed) {
	if (isValid(newSpeed))
		speed = newSpeed;
	else
		speed = 0;
	return this;
}

uint8_t LCDSpicer2::Speed::getSpeed() const {
	return speed;
}
