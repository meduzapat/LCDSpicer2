/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Direction.cpp
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
#include "Direction.hpp"

using namespace LCDSpicer2;

const array<const char*, 4> Direction::DIRECTIONS = {
	"Left to Right",
	"Right to Left",
	"Down to Up",
	"Up to Down"
};

Direction::Direction(uint8_t direction) {
	setDirection(direction);
}

bool Direction::isValid(uint8_t direction) {
	return (direction >= LEFT_RIGHT and direction <= UP_DOWN);
}

Direction* Direction::setDirection(uint8_t newDirection) {
	if (not isValid(newDirection))
		newDirection = LEFT_RIGHT;
	direction = newDirection;
	return this;
}

uint8_t Direction::getDirection() {
	return direction;
}
