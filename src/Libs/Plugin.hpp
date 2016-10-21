/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Plugin.hpp
 * @ingroup		Plugins
 * @defgroup	outputPlugins Output Plugins
 * @defgroup	inputPlugins Input Plugins
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

#ifndef SRC_LIBS_PLUGIN_HPP_
#define SRC_LIBS_PLUGIN_HPP_ 1

// To handle unordered map.
#include <unordered_map>

#include <vector>
using std::vector;

// To write logs.
#include "Logger.hpp"

#include "Definitions.hpp"

namespace LCDSpicer2 {

/**
 * @name Possible plugins status
 * @{
 */
/// The plugin failed to connect or initialize, is recoverable and can be restarted.
#define STATUS_OFFLINE	0

/// All clear.
#define STATUS_OK		1

/// The plugin is OK but is not processing requests (will be ignored).
#define STATUS_AWAY		2

/// The plugin is OK but is waiting for some I/O (will be ignored).
#define STATUS_WAITING	3

/// The plugin is not working correctly and need to be detached / terminated (will be unload).
#define STATUS_UNSTABLE	4
/// @}

/// To avoid loading incompatible plugins.
#define PLUGIN_API_VERSION 2

/**
 * Class with methods and libraries shared between input and output plugins.
 */
class Plugin {

public:

	Plugin();

	virtual ~Plugin() {};

	/**
	 * Initialization function.
	 *
	 * @return true on success false instead.
	 */
	virtual bool initialize() = 0;

	/**
	 * Returns the API version used.
	 * @return
	 */
	virtual const int getApiVersion() final;

	/**
	 * This is the first method called after the plugin creation.
	 *
	 * @param configuration a map with all the values coming from the configuration file.
	 */
	virtual void setConfiguration(umap<string, Value> configuration) final;

protected:

	/**
	 * Get a configuration value.
	 *
	 * @param key
	 * @param[out] value
	 * @return True on success, false if the key doesn't exist.
	 */
	virtual bool getConfigurationValue(const string& key, Value& value) final;

	/// Instance of the logger.
	Logger* logger = nullptr;

private:

	/// Plugins configuration is provided using this map.
	umap<string, Value> configuration;
};

}
#endif /* SRC_LIBS_PLUGIN_HPP_ */
