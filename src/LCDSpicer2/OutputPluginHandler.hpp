/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		OutputPluginHandler.hpp
 * @ingroup		LCDSpicer2
 * @since		Oct 27, 2015
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

#ifndef SRC_LCDSPICER2_OUTPUTPLUGINHANDLER_HPP_
#define SRC_LCDSPICER2_OUTPUTPLUGINHANDLER_HPP_

#include "OutputPlugin.hpp"
#include "PluginHandler.hpp"
#include "Rotation.hpp"


namespace LCDSpicer2 {

#define OUTPUT_PLUGIN_PATH PACKAGE_DATA_DIR OUTPUT_SUB_DIR

/**
 * OutputPluginHandler.
 *
 * This class handlers the output plugins, taking care of creating and destroying them.
 */
class OutputPluginHandler : public PluginHandler {

public:

	/**
	 * Creates a new handler that will attempt to Initialize the plugin from the path.
	 *
	 * @param pluginName
	 * @param pluginPath
	 * @param fullCapabilities if set to true will extract everything.
	 * @throws LCDSpicer2::Error if the load fails.
	 */
	OutputPluginHandler(string& pluginName, string& pluginPath);

	/**
	 * Clean up.
	 */
	virtual ~OutputPluginHandler();

	void initialize(bool fullCapabilities = true);

	/**
	 * Starts the screen rotation.
	 */
	void run();

	/**
	 * Direct access to the output plugin.
	 *
	 * @return a pointer to the LCD output plugin.
	 */
	OutputPlugin* getLCD() const;

	/**
	 * Change the current screen to the next.
	 * @return the id of the new screen been displayed.
	 */
	id_t selectScreen();

	/**
	 * Stores the screen cycle value.
	 *
	 * @param screenCycle
	 */
	void setScreenRotation(Rotation& screenRotation);

	/**
	 * Return the active screen id;
	 *
	 * @return returns 0 if none.
	 */
	id_t getActiveScreenId();

	/**
	 * Returns if the plugin needs to rotate the current screen.
	 *
	 * @return true if rotation is needed.
	 */
	bool needsScreenRotation();

	/**
	 * Returns the output plugin capabilities.
	 *
	 * @return the JSON representation of the output plugin capabilities.
	 */
	string showPluginCapabilities();

private:

	/// Keeps an instance of the output plugin.
	OutputPlugin* instance;

	/// Stores the screen cycle type.
	Rotation screenRotation;

	/// Keeps the direction, used to handle the reverse directions.
	bool movingForward = true;

	/// The current active screen id.
	id_t activeScreenId = 0;

	/// Keeps a list of the Ids for every screen.
	vector<id_t> screensId;

//	id_t ScreenCycler::previous(); TODO nice feature to implement.

	/**
	 * Force the display of a specific screens,
	 * if the screen id doens't exist nothing happens.
	 *
	 * @param id
	 */
	void moveTo(id_t id);

	/**
	 * Extracts widgets information.
	 *
	 * @return JSON string with the widget information.
	 */
	string processWidget();

	/**
	 * Extracts widget's parameters.
	 *
	 * @param parameters an array of parameters.
	 * @return JSON string with the parameters information.
	 */
	string processParameters(vector<Parameter>& parameters);

};

}

#endif /* SRC_LCDSPICER2_OUTPUTPLUGINHANDLER_HPP_ */
