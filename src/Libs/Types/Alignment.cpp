/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Alignment.cpp
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
#include "Alignment.hpp"

using namespace LCDSpicer2;

const array<const char*, 3> Alignment::ALIGNMENTS = {
	"Left",
	"Right",
	"Center"
};

Alignment::Alignment(uint8_t alignment) {
	setAlignment(alignment);
}

const bool Alignment::isValid(uint8_t alignment) {
	return (alignment >= LEFT and alignment <= CENTER);
}

Alignment* Alignment::setAlignment(uint8_t newAlignment) {
	if (not isValid(newAlignment))
		newAlignment = LEFT;
	alignment = newAlignment;
	return this;
}

uint8_t Alignment::getAlignment() {
	return alignment;
}
