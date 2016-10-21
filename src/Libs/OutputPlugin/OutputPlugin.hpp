/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		OutputPlugin.hpp
 * @ingroup		outputPlugins
 * @since		Dec 18, 2013
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

#ifndef SRC_LIBS_OUTPUTPLUGIN_OUTPUTPLUGIN_HPP_
#define SRC_LIBS_OUTPUTPLUGIN_OUTPUTPLUGIN_HPP_ 1

// To use queues.
#include <queue>
using std::queue;

#include "Plugin.hpp"
#include "Screen.hpp"
#include "OutputDefinitions.hpp"

namespace LCDSpicer2 {

/**
 * OutputPlugin.
 *
 * Base class to handle output plugins.
 */
class OutputPlugin : public Plugin {

public:

	/**
	 * Remove screens when finish.
	 */
	virtual ~OutputPlugin();

	/**
	 * Adds a new screen with the provided id.
	 *
	 * @param id
	 * @param seconds
	 * @return a new created screen.
	 */
	virtual Screen* addScreen(id_t id, uint64_t seconds) final;

	/**
	 * Returns a pointer to the screen with the screenId id.
	 *
	 * @param screenId the id of the screen to get
	 * @return a pointer to a screen.
	 */
	Screen* getScreen(id_t screenId);

	/**
	 * Returns a pointer to the current screen.
	 *
	 * @return a pointer to a screen.
	 */
	Screen* getActiveScreen();

	/**
	 * Returns the list of screens stored on this plugin.
	 *
	 * @return
	 */
	virtual const vector<id_t> getScreenIds() const final;

	/**
	 * Sets the pointer to the buttons queue.
	 *
	 * @param pool
	 */
	virtual void setButtonsPool(queue<uint8_t>* pool) final;

	/**
	 * Refresh the elements on the plugin and captures any button input.
	 */
	virtual uint8_t refresh() = 0;

	/**
	 * Change the screen with a new one.
	 *
	 * @param screenId the screen to been displayed.
	 */
	virtual void toggleScreen(id_t screenId) final;

	/**
	 * Returns what widgets this plugin can handle.
	 *
	 * @return an array with the widget codes
	 */
	virtual vector<Widget*> getAvailableWidgets() = 0;

	uint8_t getBitColors() const {
		return bitColors;
	}

	bool isGraphical() const {
		return graphical;
	}

	const Dimension& getScreenSize() const {
		return screenSize;
	}

protected:

	/**
	 * The current screen.
	 */
	Screen* activeScreen = nullptr;

	/**
	 * The screens stored by this plugin.
	 */
	umap<id_t, Screen*> screens;

	/**
	 * Create a new empty Screen and return a pointer to control it.
	 *
	 * @return a pointer to the new created screen.
	 */
	virtual Screen* createScreen(uint64_t seconds) = 0;

	/**
	 * When a button is pressed on the Output plugin this method need to be called with the button ID.
	 * @note invalid or unknown codes are ignored.
	 *
	 * @param buttonCode
	 */
	virtual void registerButtonEvent(id_t buttonCode) final;

	/// Instance of the logger.
	Logger * logger;

	/// If the hardware supports drawing graphics.
	bool graphical = false;

	/// Number of colors in bits.
	uint8_t bitColors = 1;

	/// The screen size, pixels for graphical, characters for text.
	Dimension screenSize;

private:

	/// A queue to store the button events.
	queue<uint8_t>* buttonsPool = nullptr;
};

}

// The functions to create and destroy the output plugin.
#define outputPluginFactory(plugin)															\
	extern "C" LCDSpicer2::OutputPlugin* createPlugin() { return new plugin; }					\
	extern "C" void destroyPlugin(LCDSpicer2::OutputPlugin *instance) { delete instance; }

#endif /* SRC_LIBS_OUTPUTPLUGIN_OUTPUTPLUGIN_HPP_ */
