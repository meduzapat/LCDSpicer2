/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Dimension.cpp
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
#include "Dimension.hpp"

using namespace LCDSpicer2;

Dimension::Dimension(uint32_t width, uint32_t height) {
	setWidth(width);
	setHeight(height);
}

Dimension* Dimension::setHeight(uint32_t height) {
	this->height = height;
	return this;
}

Dimension* Dimension::setWidth(uint32_t width) {
	this->width = width;
	return this;
}

uint32_t Dimension::getHeight() const {
	return height;
}

uint32_t Dimension::getWidth() const {
	return width;
}
