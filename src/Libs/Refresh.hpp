/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Refresh.hpp
 * @ingroup		LCDSpicer2
 * @date		Mar 27, 2014
 * @author		Patricio A. Rossi (MeduZa)
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

#ifndef REFRESH_HPP_
#define REFRESH_HPP_

// To handle time
#include <chrono>
using std::ratio;
using std::chrono::duration;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

namespace LCDSpicer2 {

/// In milliseconds, 20 times per second = 50/1000ms.
#define TICK 50

/// The duration nanoseconds.
#define AFFINITY 1000

/// The number of times per second that the program ticks.
#define TIMES_PER_SECOND (AFFINITY / TICK)

/// Alias
#define TimePoint steady_clock::time_point

/// LCDSpicer2 minimal unit of time.
typedef duration<int, ratio<TICK, 1000>> Tick;

/**
 * Refresh.
 *
 * Class that can handle interval of time between refresh and the last updated mark, in microseconds.
 */
class Refresh {

public:

	/**
	 * Creates a new refresh with an interval of 50/1000 milliseconds (1/20 of a second) 20 times per second.
	 *
	 * @param interval the number of Ticks to wait.
	 */
	Refresh(uint64_t interval);

	/**
	 * Changes the internal refresh interval.
	 *
	 * @param newInterval the new number of Ticks.
	 */
	void changeInterval(uint64_t newInterval);

	/**
	 * Restart the cycle.
	 */
	void mark();

	/**
	 * Returns true if the period is completed.
	 *
	 * @return true if time is due, false otherwise.
	 */
	bool isDue();

protected:

	/// Stores the refresh rate (in Ticks).
	Tick		interval;

	/// Stores the future time when the cycle will be complete.
	TimePoint	done;

	/// Flag to control of the Refresh is disabled.
	bool		disabled;
};

}

#endif /* REFRESH_HPP_ */
