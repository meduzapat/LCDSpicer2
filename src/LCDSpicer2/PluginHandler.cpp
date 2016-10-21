/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		PluginHandler.cpp
 * @ingroup		LCDSpicer
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

#include "PluginHandler.hpp"

using namespace LCDSpicer2;

// Static Initialization.
Configuration* PluginHandler::configurationHandler = nullptr;
Logger* PluginHandler::logger = nullptr;

void PluginHandler::setConfigurationHandler(Configuration& configurationHandler) {
	PluginHandler::configurationHandler = &configurationHandler;
}

PluginHandler::PluginHandler(string& pluginName, string& pluginPath) {

	// do no move.
	name = pluginName;
	path = pluginPath;

	logger = Logger::getInstance();

	string fileName = path + name + ".so";

	// Attempts to load plugin.
	LOG(Logger::DEBUG, "Attempting to load the plugin " + name + " from " + path);

	// Initialize errors.
	dlerror();
	handler = dlopen(fileName.c_str(), RTLD_NOW); //RTLD_LAZY);RTLD_GLOBAL);

	if (not handler) {
		// Failed, really sad :( lets throw like a baby.
		LOG(Logger::CRITICAL, "Unable to initialize plugin " + name);
		throw Error(dlerror());
	}
}

string PluginHandler::getName() {
	return name;
}

inline void PluginHandler::lock() {
	semaphore.lock();
}

inline bool PluginHandler::tryLock() {
	return semaphore.try_lock();
}

inline void PluginHandler::unLock() {
	semaphore.unlock();
}

vector<string> PluginHandler::getPlugins(uint8_t type) {
	string path = "" PACKAGE_LIB_DIR;
	path.append(type == INPUT ? INPUT_SUB_DIR : OUTPUT_SUB_DIR);

	vector<string> plugins;

	try {
		for (string pluginFile : getDirectoryFiles(path)) {
			string extension = pluginFile.substr(pluginFile.find('.'));
			if (extension == ".so")
				plugins.push_back(pluginFile.substr(0, pluginFile.find('.')));
		}
	}
	catch (...) {
		throw Error("Unable to get input plugins list");
	}

	return plugins;
}
