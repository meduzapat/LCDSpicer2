/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LCDProcScreen.cpp
 * @ingroup		LCDProcOutputPlugin
 * @since		Jan 16, 2016
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

#include "LCDProcScreen.hpp"

uint LCDProcScreen::screenCounter = 1;

LCDProcScreen::LCDProcScreen(
		const uint64_t seconds,
		queue<string>* const messagesPool,
		const LCDSpicer2::Dimension* const fontSize,
		const LCDSpicer2::Dimension* const screenSize
	) :
		messagesPool(messagesPool),
		fontSize(fontSize),
		screenSize(screenSize),
		Screen(seconds) {
	screenName = screenCounter++;
	changeCall = "screen_set s" + std::to_string(screenName) + " ";

	messagesPool->push("screen_add s" + std::to_string(screenName) + "\n");
	messagesPool->push(changeCall + "-priority hidden\n");
	messagesPool->push(changeCall + "-heartbeat off\n");
	messagesPool->push(changeCall + "-cursor off\n");
};

LCDSpicer2::Widget* LCDProcScreen::createWidget(
		parameter_t type,
		LCDSpicer2::Position& position,
		LCDSpicer2::Dimension& dimension,
		uint64_t ticks
	) {

	switch (type) {

	case LCDSpicer2::Widget::TEXT:
		return new LCDProcTextWidget(position, dimension, ticks, messagesPool, screenSize, screenName);

	case LCDSpicer2::Widget::BAR:
		return new LCDProcBarWidget(position, dimension, ticks, messagesPool, fontSize, screenSize, screenName);

	case LCDSpicer2::Widget::CLOCK:
		return new LCDProcClockWidget(position, dimension, ticks, messagesPool, screenSize, screenName);
	}

	return nullptr;
}

void LCDProcScreen::turnOff() {
	messagesPool->push(changeCall + " -priority hidden\n");
}

void LCDProcScreen::turnOn() {
	messagesPool->push(changeCall + " -priority alert\n");
}

umap<id_t, Specification> LCDProcScreen::getSpecifications() {
	umap<id_t, Specification> specifications;
	return specifications;
}
