/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		OutputPluginHandler.cpp
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

#include "OutputPluginHandler.hpp"

using namespace LCDSpicer2;

OutputPluginHandler::OutputPluginHandler(string& pluginName, string& pluginPath) : PluginHandler(pluginName, pluginPath) {
	instance = nullptr;
}

OutputPluginHandler::~OutputPluginHandler() {

	if (not handler)
		return;

	LOG(Logger::DEBUG, "Unloading Plugin " + name);

	// Initialize errors.
	dlerror();

	// Connecting destroyPlugin function.
	typedef void (*destroyPlugin_t)(OutputPlugin* instance);
	destroyPlugin_t destroyPlugin = (destroyPlugin_t) dlsym(handler, "destroyPlugin");

	// Check for errors.
	const char* dlsymError = dlerror();

	if (dlsymError) {
		LOG(Logger::CRITICAL, "Unable to connect the destroyPlugin function on plugin " + name);
		LOG(Logger::CRITICAL, dlsymError);
	}
	else {
		// Finalize the plugin.
		destroyPlugin(instance);
		instance = nullptr;
	}

	// End handler.
	dlclose(handler);
	handler = nullptr;

}

void OutputPluginHandler::initialize(bool fullCapabilities) {

	LOG(Logger::DEBUG, "Initializing output plugin " + name);

	dlerror();

	// Connecting initialization function.
	typedef OutputPlugin* (*createPlugin_t)();
	createPlugin_t createPlugin = (createPlugin_t) dlsym(handler, "createPlugin");

	// Check for errors.
	const char* dlsymError = dlerror();

	if (dlsymError) {
		LOG(Logger::CRITICAL, "Unable to connect the createPlugin function on the plugin " + name);
		throw Error(dlsymError);
	}

	LOG(Logger::DEBUG, "Calling createPlugin function on plugin " + name);
	// Get a plugin instance.
	instance = createPlugin();

	// Checking for plugin's API version.
	if (instance->getApiVersion() != PLUGIN_API_VERSION)
		throw Error("Plugin " + name + " is version " + std::to_string(instance->getApiVersion()) + " and is not compatible with this API version " + std::to_string(PLUGIN_API_VERSION));

	// Set the path and name.
	Value vName, vPath;
	vName.set(name);
	vPath.set(path);
	umap<string, Value> configuration;
	try {
		configuration = configurationHandler->getGroupSettings(name);
	}
	catch (...) {
		LOG(Logger::NOTICE, "Missing configuration for plugin " + name);
	}

	configuration.insert({"name", std::move(vName)});
	configuration.insert({"path", std::move(vPath)});

	// Initialize plugin.
	instance->setConfiguration(std::move(configuration));

	if (not instance->initialize()) {
		throw Error("Plugin " + name + " failed to initialize");
	}
}

id_t OutputPluginHandler::getActiveScreenId() {
	return activeScreenId;
}

bool OutputPluginHandler::needsScreenRotation() {
	return instance->getActiveScreen()->isDue();
}

void OutputPluginHandler::run() {
	// Activate the first screen.
	activeScreenId = screensId.front();
	instance->toggleScreen(activeScreenId);
}

OutputPlugin* OutputPluginHandler::getLCD() const {
	return instance;
}

void OutputPluginHandler::setScreenRotation(Rotation& screenRotation) {

	this->screenRotation = std::move(screenRotation);
	movingForward = this->screenRotation.isForward();
	screensId = instance->getScreenIds();
	screensId.shrink_to_fit();

	if (screensId.size() == 1)
		this->screenRotation = Rotation::STAY;
	else if (this->screenRotation.getRotation() == Rotation::RANDOM)
		srand(uint64_t(&this->screenRotation));
}

id_t OutputPluginHandler::selectScreen() {

	switch (screenRotation.getRotation()) {

	case Rotation::STAY:
		if (not activeScreenId)
			activeScreenId = screensId.front();
		return activeScreenId;

	case Rotation::RANDOM:
		id_t r;
		do {
			r = rand() % screensId.size() + 1;
		}
		while (r == activeScreenId);
		activeScreenId = r;
	break;

	case Rotation::CAROUSEL:

		if (screenRotation.isForward())
			for (auto i = screensId.begin(); i != screensId.end(); i++) {
				if (i + 1 == screensId.end()) {
					activeScreenId = *screensId.begin();
					break;
				}
				if (*i == activeScreenId) {
					activeScreenId = *(i + 1);
					break;
				}
			}
		else
			for (auto i = screensId.rbegin(); i != screensId.rend(); i++) {
				if (i + 1 == screensId.rend()) {
					activeScreenId = *screensId.rbegin();
					break;
				}
				if (*i == activeScreenId) {
					activeScreenId = *(i + 1);
					break;
				}
			}
	break;

	case Rotation::PINGPONG:
		if (movingForward)
			for (auto i = screensId.begin(); i != screensId.end(); i++) {
				if (i + 1 == screensId.end()) {
					activeScreenId = *(i - 1);
					movingForward = false;
					break;
				}
				if (*i == activeScreenId) {
					activeScreenId = *(i + 1);
					break;
				}
			}
		else
			for (auto i = screensId.rbegin(); i != screensId.rend(); i++) {
				if (i + 1 == screensId.rend()) {
					activeScreenId = *(i - 1);
					movingForward = true;
					break;
				}
				if (*i == activeScreenId) {
					activeScreenId = *(i + 1);
					break;
				}
			}
	break;
	}

	instance->toggleScreen(activeScreenId);

	return activeScreenId;
}

void OutputPluginHandler::moveTo(id_t id) {
	id_t screenId = 0;
	try {
		screenId = screensId.at(id);
	}
	catch (...) {}
	if (screenId and screenId != activeScreenId) {
		instance->toggleScreen(screenId);
		activeScreenId = screenId;
	}
}

string OutputPluginHandler::showPluginCapabilities() {

	return "\"" + name + "\":{"
"\"graphical\":"	+ (instance->isGraphical() ? "true" : "false") + ","
"\"bitColors\":"	+ std::to_string(instance->getBitColors()) + ","
"\"screenSizeX\":"	+ std::to_string(instance->getScreenSize().getWidth()) + ","
"\"screenSizeY\":"	+ std::to_string(instance->getScreenSize().getHeight()) + ","
"\"widgets\":{" + processWidget() + "}}";
};

string OutputPluginHandler::processWidget() {
	string out;
	for (auto widget : instance->getAvailableWidgets()) {
		Specification spec = widget->getSpecification();
		out += std::to_string(widget->getType()) + ":{"
		"\"movableX\":"		+ (spec.movable.getX() ? "true" : "false") + ","
		"\"movableY\":"		+ (spec.movable.getY() ? "true" : "false") + ","
		"\"resisableX\":"	+ (spec.resizable.getX() ? "true" : "false") + ","
		"\"resisableY\":"	+ (spec.resizable.getY() ? "true" : "false") + ","
		"\"sizeW\":"		+ std::to_string(spec.size.getWidth()) + ","
		"\"sizeH\":"		+ std::to_string(spec.size.getHeight()) + ","
		"\"minRefresh\":"	+ std::to_string(spec.minRefresh) + ","
		"\"allowedDataTypes\":" + std::to_string(spec.allowedDataTypes) + ","
		"\"parameters\":{" + processParameters(spec.parameters) + "}"
		"},";
	}
	out.resize(out.size() - 1);
	return out;
}

string OutputPluginHandler::processParameters(vector<Parameter>& parameters) {

	if (parameters.empty()) {
		return "";
	}

	string out;
	for (auto parameter : parameters) {
		out += "\"" + parameter.name + "\":{"
			"\"type\":" + std::to_string(parameter.type) + ","
			"\"values\":[";
		if (not parameter.values.empty()) {
			for (string value : parameter.values) {
				out += "\"" + value + "\",";
			}
			out.resize(out.size() - 1);
		}
		out += "]},";
	}
	out.resize(out.size() - 1);
	return out;
}
