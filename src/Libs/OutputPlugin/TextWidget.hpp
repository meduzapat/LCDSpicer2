/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		TextWidget.hpp
 * @ingroup		outputPlugins
 * @since		Nov 21, 2015
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

#ifndef SRC_LIBS_OUTPUTPLUGIN_TEXTWIDGET_HPP_
#define SRC_LIBS_OUTPUTPLUGIN_TEXTWIDGET_HPP_ 1

#include "Widget.hpp"
#include "Alignment.hpp"
#include "Direction.hpp"
#include "Speed.hpp"

namespace LCDSpicer2 {

/**
 * LCDSpicer2::TextWidget.
 *
 * Special Widget to display text.
 * @todo orientation.
 * @todo scroll.
 * @todo color.
 */
class TextWidget: public Widget, protected Alignment, protected Direction, protected Speed {

public:

	TextWidget(Position& position, Dimension& dimension, uint64_t ticks = 0);

	virtual ~TextWidget() {};

	uint8_t getType();

	virtual Specification getSpecification();

protected:

	/// Space added to the sizes to align a value.
	string strValue;

	/**
	 * @name wrapper methods.
	 *
	 * @param value
	 * @{
	 */
	void setAlignmentWrapper(Value& value);

	void setDirectionWrapper(Value& value);

	void setFontSizeWrapper(Value& value);

	void setSpeedWrapper(Value& value);
	/// @}

	/**
	 * Aligns the value based on the width.
	 */
	void alignValue();

private:

	/// Keeps the spacing to use on the sides of the value.
	string addLeft, addRight;

	/// Font size in units.
	uint32_t fontSize = 1;

	/// keeps the last size to avoid a new calculation in the case that is the same.
	uint32_t lastSize = 0;

};

} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_OUTPUTPLUGIN_TEXTWIDGET_HPP_ */
