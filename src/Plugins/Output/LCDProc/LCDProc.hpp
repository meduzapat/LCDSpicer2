/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		LCDProc.hpp
 * @defgroup	LCDProcOutputPlugin LCDProc Output Plugin
 * @ingroup		outputPlugins
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

#ifndef SRC_PLUGINS_OUTPUT_LCDPROC_LCDPROC_HPP_
#define SRC_PLUGINS_OUTPUT_LCDPROC_LCDPROC_HPP_ 1

#include <unistd.h>

#include "Socks.hpp"
#include "LCDProcScreen.hpp"
#include "OutputPlugin.hpp"

/**
 * LCDProc.hpp
 *
 * LCDProc output plugin.
 */
class LCDProc : public LCDSpicer2::OutputPlugin, public LCDSpicer2::Socks {

public:

	virtual ~LCDProc();

	bool initialize();

	uint8_t refresh();

	LCDSpicer2::Screen* createScreen(uint64_t seconds);

	vector<LCDSpicer2::Widget*> getAvailableWidgets();

private:

	/**
	 * Process the answer from LCDd and react based on the target.
	 * @param data the answer from LCDd.
	 * @param target the element to look for.
	 */
	void processAnswer(const string& data, const string& target);

	/// Maximum number of messages to send in one transmission.
	uint8_t commandsToSend	= 10;

	/// Time to wait between messages sent to LCDd to avoid overflow.
	uint64_t affinity		= 10000;

	/// Queue of messages from the screens and widgets to be send to LCDd.
	queue<string> messagesPool;

	/// Keeps the font size.
	LCDSpicer2::Dimension fontSize;

	/// LCDd keys to LCDSpicer keys mapping
	/// @todo finish this.
	umap<string, uint8_t> keymap = {
		{"Escape",		BUTTON_ESC	},
		{"Enter",		BUTTON_ENTER},
		{"Left"	,		BUTTON_LEFT },
		{"Right",		BUTTON_RIGHT},
		{"Up",			BUTTON_UP	},
		{"Down",		BUTTON_DOWN }
	};

};

#endif /* SRC_PLUGINS_OUTPUT_LCDPROC_LCDPROC_HPP_ */
