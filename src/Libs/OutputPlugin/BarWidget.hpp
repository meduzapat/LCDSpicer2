/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		BarWidget.hpp
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

#ifndef SRC_LIBS_OUTPUTPLUGIN_BARWIDGET_HPP_
#define SRC_LIBS_OUTPUTPLUGIN_BARWIDGET_HPP_

#include "Widget.hpp"
#include "Direction.hpp"

namespace LCDSpicer2 {

/**
 * LCDSpicer2::BarWidget.
 *
 * Special Widget to display percent bars.
 * @todo orientation.
 * @todo style.
 * @todo color.
 */
class BarWidget: public Widget, protected Direction {

public:

	BarWidget(Position& position, Dimension& dimension, uint64_t ticks = 0);

	virtual ~BarWidget() {};

	uint8_t getType();

	virtual Specification getSpecification();

protected:

	void setDirectionWrapper(Value& value);

};

} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_OUTPUTPLUGIN_BARWIDGET_HPP_ */
