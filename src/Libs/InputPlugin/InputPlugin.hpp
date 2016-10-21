/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		InputPlugin.hpp
 * @ingroup		inputPlugins
 * @since		Dec 17, 2013
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

#ifndef SRC_LIBS_INPUT_PLUGIN_HPP_
#define SRC_LIBS_INPUT_PLUGIN_HPP_ 1

#include "Plugin.hpp"

#include "Refresh.hpp"

#include <functional>

#include "InputDefinitions.hpp"
using callBack_t = std::function<void(id_t, id_t, umap<string, string>)>;


namespace LCDSpicer2 {

/**
 * Base class to handle input plugins.
 */
class InputPlugin : public Plugin {

public:

	~InputPlugin();


	Value* registerValue(id_t functionId, id_t subFunctionId,const string& data);

	/**
	 * Request an update on the value.
	 *
	 * @param requestData The request information to execute the action.
	 * @param force Forces the value to get updated.
	 * @return The new Value.
	 */
	void update(RequestData& requestData, bool force = false);

	/**
	 * Populates the necessary function values for the different sub functions.
	 */
	virtual void detectFunctionsValues(callBack_t callBack) = 0;

	/**
	 * Changes the refresh rate for a function.
	 *
	 * @param function
	 * @param newRefresh
	 */
	void setFunctionRefreshRate(id_t function, uint64_t newRefresh);

protected:

	/**
	 * Method to handle the different requests.
	 *
	 * @param requestData
	 */
	virtual Value processRequest(const RequestData& requestData) = 0;

private:

	/// Cache to the values.
	umap<id_t, umap<id_t, umap<string, Value>>> values;

	/**
	 * Keeps the different refresh for functions,
	 * used as a cache for the input plugins to know if a function was refreshed or not.
	 * Useful to group sub-functions of the same kind that updates from the same source.
	 */
	umap<id_t, Refresh*> internalRefresh;

};

}

// The functions to create and destroy the input plugin.
#define inputPluginFactory(plugin)																\
	extern "C" LCDSpicer2::InputPlugin* createPlugin() { return new plugin; }					\
	extern "C" void destroyPlugin(LCDSpicer2::InputPlugin* instance) { delete instance; }

#endif /* SRC_LIBS_INPUT_PLUGIN_HPP_ */
