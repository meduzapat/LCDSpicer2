/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		PluginHandler.hpp
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

#ifndef SRC_LCDSPICER2_PLUGINHANDLER_HPP_
#define SRC_LCDSPICER2_PLUGINHANDLER_HPP_ 1

#include <vector>
using std::vector;

// For dlopen.
#include <dlfcn.h>

// Semaphores.
#include <mutex>
using std::mutex;

// Logging utility.
#include "Logger.hpp"

// To read configuration files.
#include "Configuration.hpp"

// To use generic functions.
#include "GenericFunctions.hpp"

/// Code for output plugins
#define OUTPUT	0
/// Code for input plugins
#define INPUT	1

/// Sub directory for output plugins
#define OUTPUT_SUB_DIR "/plugins/output/"

/// Sub directory for input plugins
#define INPUT_SUB_DIR "/plugins/input/"

namespace LCDSpicer2 {

/**
 * LCDSpicer2::PluginHandler.
 *
 * Basic functionality for plugins.
 */
class PluginHandler {

public:

	/**
	 * Creates a new PluginHandler.
	 *
	 * @param pluginName
	 * @param path
	 * @throws LCDSpicer2::Error if fails to load the plugin.
	 */
	PluginHandler(string& pluginName, string& path);

	/**
	 * Initialization method, is called from the constructor when we create the object for the first time.
	 *
	 * @param fullCapabilities if set to true will extract everything.
	 * @throws LCDSpicer2::Error if something goes wrong.
	 */
	virtual void initialize(bool fullCapabilities = false) = 0;

	/**
	 * Clean up.
	 */
	virtual ~PluginHandler() {};

	/**
	 * Sets the configuration handler to read the settings for the different plugins.
	 *
	 * @param configurationHandler A pointer to the configuration handler.
	 */
	static void setConfigurationHandler(Configuration& configurationHandler);

	/**
	 * Return the plugin's name.
	 *
	 * @return string with the name.
	 */
	string getName();

	/**
	 * Returns a list of plugins.
	 *
	 * @return a vector with the plugin names.
	 */
	static vector<string> getPlugins(uint8_t type);

	/**
	 * Method that returns the plugin capabilities.
	 *
	 * @return JSON string of capabilities.
	 */
	virtual string showPluginCapabilities() = 0;

	/**
	 * Looks the internal semaphore.
	 */
	virtual void lock() final;

	/**
	 * Attempts to lock the semaphore.
	 */
	virtual bool tryLock() final;

	/**
	 * Unlocks the internal semaphore.
	 */
	virtual void unLock() final;

protected:

	/// Stores the dlopen handler.
	void* handler = nullptr;

	/// Keeps the name for logging, but not important.
	string name;

	/// Keeps the path for logging and reference, but not important.
	string path;

	/// Keeps a copy of the configuration handler until initialization.
	static Configuration* configurationHandler;

	/// Logger instance.
	static Logger* logger;

	/// Semaphore to avoid collisions when updating.
	mutex semaphore;
};

}

#endif /* SRC_LCDSPICER2_PLUGINHANDLER_HPP_ */
