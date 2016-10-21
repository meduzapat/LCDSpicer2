/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		InputPluginHandler.cpp
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

#include <functional>
using namespace std::placeholders;

#include "InputPluginHandler.hpp"
#include "InputPluginManifest.hpp"

using namespace LCDSpicer2;

InputPluginHandler::InputPluginHandler(string& pluginName, string& pluginPath) :
PluginHandler(pluginName, pluginPath) {
	instance	= nullptr;
}

InputPluginHandler::~InputPluginHandler() {

	if (not handler)
		return;

	LOG(Logger::DEBUG, "Unloading Plugin " + name);

	// Initialize error.
	dlerror();
	// Connecting destroyPlugin function.
	typedef void (*destroyPlugin_t)(InputPlugin* instance);
	destroyPlugin_t destroyPlugin = (destroyPlugin_t) dlsym(handler, "destroyPlugin");

	// Check for errors.
	const char* dlsymError = dlerror();

	if (dlsymError) {
		LOG(Logger::CRITICAL, "Unable to connect the destroyPlugin function on plugin " + name);
		LOG(Logger::CRITICAL, dlsymError);
	}
	else {
		// Finalize the plugin
		destroyPlugin(instance);
		instance = nullptr;
	}

	// End handler.
	dlclose(handler);
	handler = nullptr;
}

void InputPluginHandler::initialize(bool fullCapabilities) {

	LOG(Logger::DEBUG, "Loading configuration and initializing Input plugin " + name);
	umap<string, Value> configuration;
	try {
		configuration = configurationHandler->getGroupSettings(name);
	}
	catch (...) {
		LOG(Logger::NOTICE, "Missing configuration for plugin " + name);
	}

	dlerror();

	// Connecting initialization function.
	typedef InputPlugin* (*createPlugin_t)();
	createPlugin_t createPlugin = (createPlugin_t) dlsym(handler, "createPlugin");

	// Check for errors.
	const char* dlsym_error = dlerror();

	if (dlsym_error) {
		LOG(Logger::CRITICAL, "Unable to connect the createPlugin function on the plugin " + name);
		throw Error(dlsym_error);
	}

	LOG(Logger::DEBUG, "Calling createPlugin function on plugin " + name);
	// Get a plugin instance.
	instance = createPlugin();

	// Checking for plugin's API version.
	if (instance->getApiVersion() != PLUGIN_API_VERSION)
		throw Error("Plugin " + name + " is version " + std::to_string(instance->getApiVersion()) + " and is not compatible with this API version " + std::to_string(PLUGIN_API_VERSION));

	// Set the successful path and name.
	Value vName, vPath;
	vName.set(name);
	vPath.set(path);
	configuration["name"] = std::move(vName);
	configuration["path"] = std::move(vPath);

	// Set parameters.
	instance->setConfiguration(std::move(configuration));

	// Initialize plugin.
	if (not instance->initialize())
		throw Error("Plugin " + name + " failed to initialize");

	readPlugingManifest(fullCapabilities);
}

InputPlugin* InputPluginHandler::getPlugin() const {
	return instance;
}

bool InputPluginHandler::functionExists(id_t function) {
	return (internalFunctions.find(function) != internalFunctions.end());
}

bool InputPluginHandler::subFunctionExists(id_t function, id_t subFunction) {
	return (internalFunctions[function].subFunctions.find(subFunction) != internalFunctions[function].subFunctions.end());
}

bool InputPluginHandler::valueIsAllowed(id_t function, id_t subFunction, const string& data) {
	// Check if data is valid only if the function do not accepts new unknown data values.
	if (not internalFunctions[function].subFunctions[subFunction].acceptCustomValues and not data.empty()) {
		bool found = false;
		for (auto value : internalFunctions[function].subFunctions[subFunction].values)
			if (value.second == data) {
				found = true;
				break;
			}
		return found;
	}
	return true;
}

Value* InputPluginHandler::registerFunction(const RequestData& requestData) {
	if (not functionExists(requestData.function))
		throw Error("Attempting to register an unknown function " + name + ":" + std::to_string(requestData.function));

	if (not subFunctionExists(requestData.function, requestData.subFunction))
		throw Error("Attempting to register an unknown sub function " + name + ":" + std::to_string(requestData.function) + ":" + std::to_string(requestData.subFunction));

	if (not valueIsAllowed(requestData.function, requestData.subFunction, requestData.data))
		throw Error("Attempting to register an unknown data element for a function that do not allow that: " + name + ":" + std::to_string(requestData.function) + ":" + std::to_string(requestData.subFunction) + ":" + requestData.data);

	return instance->registerValue(requestData.function, requestData.subFunction, requestData.data);
}

void InputPluginHandler::setFunctions(umap <id_t, Function> funtionData) {

	internalFunctions.clear();
	internalFunctions = std::move(funtionData);

	instance->detectFunctionsValues(std::bind(&InputPluginHandler::setValues, this, _1, _2, _3));
	for (auto function : internalFunctions) {
		uint64_t functionMinimumRefresh = 0;
		for (auto subFunction : function.second.subFunctions) {
			// Set the sub function parameters.
			if (not functionMinimumRefresh or functionMinimumRefresh > subFunction.second.minimunRefreshRate)
				functionMinimumRefresh = subFunction.second.minimunRefreshRate;
		}
		instance->setFunctionRefreshRate(function.first, functionMinimumRefresh);
	}
}

umap<id_t, Function>* InputPluginHandler::getFunctions() {
	return &internalFunctions;
}

void InputPluginHandler::cleanFunctions() {
	internalFunctions.clear();
}

void InputPluginHandler::setValues(id_t function, id_t subFunction, umap<string, string> values) {

	if (values.empty())
		return;

	if (not functionExists(function))
		throw Error("Attempting to set values for an unknown function " + std::to_string(function));

	if (not subFunctionExists(function, subFunction))
		throw Error("Attempting to set values for an unknown sub function " + std::to_string(function) + ":" + std::to_string(subFunction));

	internalFunctions[function].subFunctions[subFunction].values = std::move(values);
}

uint64_t InputPluginHandler::getMinimunRefresh(id_t function, id_t subFunction) {
	return internalFunctions[function].subFunctions[subFunction].minimunRefreshRate;
}

uint64_t InputPluginHandler::getMaximunRefresh(id_t function, id_t subFunction) {
	return internalFunctions[function].subFunctions[subFunction].maximunRefreshRate;
}

uint64_t InputPluginHandler::getCurrentRefresh(id_t function, id_t subFunction) {
	if (internalFunctions[function].subFunctions[subFunction].maximunRefreshRate)
		return internalFunctions[function].subFunctions[subFunction].minimunRefreshRate;
	return 0;
}

void InputPluginHandler::readPlugingManifest(bool fullRead) {

	InputPluginManifest pluginManifest(PACKAGE_DATA_DIR "/input/" + name + "/PluginManifest.xml");
	setFunctions(pluginManifest.getFunctions(fullRead));
}

string InputPluginHandler::showPluginCapabilities() {

	string capabilities = "\"" + name + "\":{";

	if (internalFunctions.size()) {
		for (auto& function : internalFunctions)
			capabilities += "\"" + std::to_string(function.first) + "\":{" + createFunctionJson(function.second) + "},";

		capabilities.resize(capabilities.size() - 1);
	}
	capabilities += "}";
	return std::move(capabilities);
}

string InputPluginHandler::createFunctionJson(Function& function) {

	string result =
"\
\"name\":\"" + function.name + "\",\
\"subFunctions\":{";

	if (function.subFunctions.size()) {
		for (auto& subFunction : function.subFunctions)
			result += "\"" + std::to_string(subFunction.first) + "\":{" + createSubFunctionJson(subFunction.second) + "},";

		result.resize(result.size()-1);
	}

	result += "}";
	return std::move(result);
}

string InputPluginHandler::createSubFunctionJson(SubFunction& subfunction) {

	string result =
"\"name\":\""				+ subfunction.name										+ "\","
"\"description\":\""		+ subfunction.description								+ "\","
"\"image\":\""				+ subfunction.image										+ "\","
"\"acceptCustomValues\":"	+ (subfunction.acceptCustomValues ? "true" : "false")	+ ","
"\"minimunRefreshRate\":"	+ std::to_string(subfunction.minimunRefreshRate)		+ ","
"\"maximunRefreshRate\":"	+ std::to_string(subfunction.maximunRefreshRate)		+ ","
"\"dataType\":"				+ std::to_string(subfunction.dataType)					+ ","
"\"symbolType\":\""			+ subfunction.symbolType								+ "\","
"\"values\":{";

	if (subfunction.values.size()) {
		for (auto value : subfunction.values)
			result += "\"" + value.first + "\":\"" + value.second + "\",";
		result.resize(result.size() - 1);
	}

	result += "}";
	return std::move(result);
}
