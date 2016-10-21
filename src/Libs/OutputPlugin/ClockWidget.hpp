/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		ClockWidget.hpp
 * @ingroup		outputPlugins
 * @since		Feb 18, 2016
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

#ifndef SRC_LIBS_OUTPUTPLUGIN_CLOCKWIDGET_HPP_
#define SRC_LIBS_OUTPUTPLUGIN_CLOCKWIDGET_HPP_ 1

#include "Widget.hpp"

namespace LCDSpicer2 {

/**
 * LCDSpicer2::ClockWidget
 */
class ClockWidget: public Widget {

public:

	/// Small clock.
	static constexpr uint8_t SMALL	= 0;
	/// Medium clock.
	static constexpr uint8_t MEDIUM	= 1;
	/// Large clock.
	static constexpr uint8_t LARGE	= 2;

	static const array<const char*, 3> SIZES;

	/// 12 hours format
	static constexpr uint8_t HRS12	= 0;
	/// 24 hours format
	static constexpr uint8_t HRS24	= 1;

	static const array<const char*, 2> FORMATS;

	ClockWidget(
		Position& position,
		Dimension& dimension,
		uint64_t ticks
	);

	virtual ~ClockWidget() {};

	uint8_t getType();

	virtual Specification getSpecification();

protected:

	/// The desired clock to draw.
	uint8_t size = SMALL;

	/// 12 or 24 hrs. format for time.
	uint8_t timeFormat = false;

	/// Keeps if the clock will display seconds.
	bool seconds = true;

	/// Leading zeroes.
	bool leadingZeroes = true;

	/**
	 * Wrapper to set the size.
	 *
	 * @param value
	 */
	void setSizeWrapper(Value value);

	/**
	 * Wrapper to set the time format.
	 *
	 * @param value
	 */
	void setFormatWrapper(Value value);

	/**
	 * Wrapper to set if the seconds will be visible or not.
	 * @param value
	 */
	void setSecondsWrapper(Value value);

	/**
	 * Wrapper to set if the leading zeroes are visible or not.
	 *
	 * @param value
	 */
	void setLeadingZeroesWrapper(Value value);
};

} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_OUTPUTPLUGIN_CLOCKWIDGET_HPP_ */
