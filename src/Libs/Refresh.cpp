/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Refresh.cpp
 * @ingroup		LCDSpicer2
 * @author		Patricio A. Rossi (MeduZa)
 * @date		Mar 27, 2014
 *
 * @copyright 	Copyright © 2015 - 2016 Patricio A. Rossi (MeduZa)
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

#include "Refresh.hpp"

using namespace LCDSpicer2;

Refresh::Refresh(uint64_t interval) {
	changeInterval(interval);
}

void Refresh::changeInterval(uint64_t newInterval) {
	if (newInterval) {
		interval = Tick(newInterval);
		disabled = false;
	}
	else {
		disabled = true;
	}
}

void Refresh::mark() {
	if (disabled)
		return;
	done = steady_clock::now() + interval;
}

bool Refresh::isDue() {
	if (disabled)
		return false;
	return (steady_clock::now() > done);
}
