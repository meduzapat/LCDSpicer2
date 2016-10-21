/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Rotation.cpp
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

#include "Rotation.hpp"

using namespace LCDSpicer2;

const string Rotation::ROTATIONS[] = {
	"Stay",
	"Random",
	"Ping Pong",
	"Carousel"
};

Rotation::Rotation(uint8_t rotation, bool forward) {
	setRotation(rotation);
	setForward(forward);
}

bool Rotation::isValid(uint8_t n) {
	return (n >= STAY and n <= CAROUSEL);
}

uint8_t Rotation::getRotation() const {
	return rotation;
}

Rotation* Rotation::setRotation(uint8_t rotation ) {
	if (isValid(rotation))
		this->rotation = rotation;
	return this;
}

bool Rotation::isForward() const {
	return forward;
}

Rotation* Rotation::setForward(bool forward) {
	this->forward = forward;
	return this;
}

