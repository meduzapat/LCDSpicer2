/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LogDumper.hpp
 * @defgroup	logDumperOutputPlugin LogDumper Output Plugin
 * @ingroup		outputPlugins
 * @since		Nov 20, 2015
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
#ifndef SRC_PLUGINS_OUTPUT_LOGDUMPER_LOGDUMPER_HPP_
#define SRC_PLUGINS_OUTPUT_LOGDUMPER_LOGDUMPER_HPP_

#include "LogDumperScreen.hpp"
#include "OutputPlugin.hpp"

/**
 * LogDumper.
 *
 * Example output plugin.
 */
class LogDumper : public LCDSpicer2::OutputPlugin {

public:

	virtual ~LogDumper();

	bool initialize();

	uint8_t refresh();

	LCDSpicer2::Screen* createScreen(uint64_t seconds);

};

#endif /* SRC_PLUGINS_OUTPUT_LOGDUMPER_LOGDUMPER_HPP_ */
