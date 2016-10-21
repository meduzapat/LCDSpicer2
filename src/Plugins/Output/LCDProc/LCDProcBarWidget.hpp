/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LCDProcBarWidget.hpp
 * @ingroup		LCDProcOutputPlugin
 * @since		jan 17, 2016
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

#ifndef SRC_PLUGINS_OUTPUT_LCDPROC_LCDPROCBARWIDGET_HPP_
#define SRC_PLUGINS_OUTPUT_LCDPROC_LCDPROCBARWIDGET_HPP_ 1

#include "BarWidget.hpp"
#include "LCDProcWidget.hpp"

/**
 * LCDProcBarWidget.
 *
 * Bar widget for LCDProc.
 */
class LCDProcBarWidget: public LCDProcWidget, public LCDSpicer2::BarWidget {

public:

	LCDProcBarWidget(
		LCDSpicer2::Position& position,
		LCDSpicer2::Dimension& dimension,
		uint64_t ticks,
		queue<string>* const messagesPool,
		const LCDSpicer2::Dimension* const fontSize,
		const LCDSpicer2::Dimension* const screenSize,
		const uint screenId
	);

	void redraw();

	virtual LCDSpicer2::Specification getSpecification();

protected:

	/// Keeps the font size.
	const LCDSpicer2::Dimension* const fontSize;

	/// Temporary len calculation.
	uint32_t len;

	void generateLCDdElement();

};

#endif /* SRC_PLUGINS_OUTPUT_LCDPROC_LCDPROCBARWIDGET_HPP_ */
