/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		InputPluginHandler.hpp
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

#ifndef SRC_LCDSPICER2_INPUTPLUGINHANDLER_HPP_
#define SRC_LCDSPICER2_INPUTPLUGINHANDLER_HPP_ 1

#include "InputPlugin.hpp"
#include "PluginHandler.hpp"

namespace LCDSpicer2 {

#define INPUT_PLUGIN_PATH PACKAGE_DATA_DIR INPUT_SUB_DIR

/**
 * InputPluginHandler.
 *
 * This class handlers the Input plugins, taking care of creating and destroying them.
 */
class InputPluginHandler : public PluginHandler {

public:

	/**
	 * Creates a new handler that will attempt to Initialize the plugin from the path.
	 *
	 * @param pluginName
	 * @param pluginPath
	 * @throws LCDSpicer2::Error if the load fails.
	 */
	InputPluginHandler(string& pluginName, string& pluginPath);

	/**
	 * Clean up.
	 */
	virtual ~InputPluginHandler();

	/**
	 * Initializes the plugin connection.
	 *
	 * @param fullCapabilities if set to true, will extract the full manifest, false will extract only functional information.
	 */
	void initialize(bool fullCapabilities = false);

	/**
	 * Direct access to the Input plugin.
	 *
	 * @return a pointer to the Input plugin.
	 */
	InputPlugin* getPlugin() const;

	/**
	 * Call this method to register a function to be available.
	 *
	 * @param requestData the request action.
	 * @returns a pointer to the value.
	 * @throws LCDSpicer2::Error if the function or sub function are unknown.
	 */
	Value* registerFunction(const RequestData& requestData);

	/**
	 * Sets the sub-function parameters.
	 *
	 * @param functionId
	 * @param functionData
	 */
	void setFunctions(umap <id_t, Function> funtionData);

	/**
	 * Returns the sub-function parameters.
	 * @return a pointer to the whole functions structure.
	 */
	umap<id_t, Function>* getFunctions();

	/**
	 * Remove the internal function parameters.
	 */
	void cleanFunctions();

	/**
	 * Function used to populate the function values.
	 *
	 * @param function the function id
	 * @param subFunction the sub function id
	 * @param values the map of values.
	 */
	void setValues(id_t function, id_t subFunction, umap<string, string> values);

	/**
	 * Returns the minimum refresh rate for a function.
	 *
	 * @param function
	 * @param subFunction
	 * @returns the refresh in TICKs.
	 */
	uint64_t getMinimunRefresh(id_t function, id_t subFunction);

	/**
	 * Returns the maximum refresh rate for a function.
	 *
	 * @param function
	 * @param subFunction
	 * @returns the refresh in TICKs.
	 */
	uint64_t getMaximunRefresh(id_t function, id_t subFunction);

	/**
	 * Returns the in use by the cache refresh rate.
	 *
	 * @param function
	 * @param subFunction
	 * @return the refresh in TICKs.
	 */
	uint64_t getCurrentRefresh(id_t function, id_t subFunction);

	/**
	 * Returns a JSON object with the plugin capabilities.
	 *
	 * @return a JSON string.
	 */
	string showPluginCapabilities();

protected:

	/// Keeps the different sub-functions parameters.
	umap<id_t, Function> internalFunctions;

	bool functionExists(id_t function);

	bool subFunctionExists(id_t function, id_t subFunction);

	bool valueIsAllowed(id_t function, id_t subFunction, const string& data);

private:

	/**
	 * Keeps an instance of the Input plugin.
	 */
	InputPlugin* instance;

	/**
	 * Reads the plugin manifest and extracts the information needed by the plugin.
	 *
	 * @param fullRead set to false to read only minimum functional information, true to read the complete record.
	 */
	void readPlugingManifest(bool fullRead);

	/**
	 * Converts functions into JSON.
	 *
	 * @param function
	 * @return a JSON string.
	 */
	string createFunctionJson(Function& function);

	/**
	 * Converts sub functions into JSON.
	 *
	 * @param subfunction
	 * @return a JSON string.
	 */
	string createSubFunctionJson(SubFunction& subfunction);

};

}

#endif /* SRC_LCDSPICER2_INPUTPLUGINHANDLER_HPP_ */
