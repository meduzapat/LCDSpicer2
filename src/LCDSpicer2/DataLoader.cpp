/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		DataLoader.cpp
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

#include "DataLoader.hpp"
#include "Configuration.hpp"
#include "GenericFunctions.hpp"

using namespace LCDSpicer2;

Logger* DataLoader::logger = nullptr;

DataLoader::DataLoader(const string& fileName) : XMLHelper(fileName) {
	logger = Logger::getInstance();
}

umap<string, umap<id_t, vector<Request>>> DataLoader::getRefreshWork() {
	return std::move(refreshWork);
}

vector<InputPluginHandler*> DataLoader::getInputPluginHandlers() {
	return std::move(inputPluginHandlers);
}

vector<OutputPluginHandler*> DataLoader::getOutputPluginHandlers() {

	string oPath = PACKAGE_LIB_DIR OUTPUT_SUB_DIR;
	string iPath = PACKAGE_LIB_DIR INPUT_SUB_DIR;

	vector<OutputPluginHandler*> outputPlugins;
	// temporary container to control duplicated plugins.
	vector<string> outputPluginNames;
	umap<string, InputPluginHandler*> inputPluginNames;

	umap<id_t, WidgetData> widgets = processWidgetNode();
	umap<id_t, ScreenData> screens = processScreenNode();

	for (OutputPluginData outputPluginData : processOutputNode()) {
		// NOTE: Changing the code here will allow multiple instances of the same output plugin.
		if (inVector(outputPluginData.name, outputPluginNames)) {
			LOG(Logger::WARNING, "Duplicated output plugin found " + outputPluginData.name);
			continue;
		}
		OutputPluginHandler* outputPluginHandler = new OutputPluginHandler(outputPluginData.name, oPath);
		outputPluginHandler->initialize();
		outputPluginNames.push_back(outputPluginData.name);
		outputPlugins.push_back(outputPluginHandler);

		OutputPlugin* outputPlugin = outputPluginHandler->getLCD();

		// Add Screens.
		for (id_t sid : outputPluginData.screens) {

			Screen* screen = outputPlugin->addScreen(sid, screens[sid].duration);
			if (not screen) {
				// Ignore when the widget type is not supported by the plugin.
				LOG(Logger::DEBUG, "Screen " + std::to_string(sid) + " ignored");
				continue;
			}

			// Custom parameters.
			for (auto& parameter : screens[sid].parameters)
				screen->update(parameter.first, parameter.second);

			// Add Widgets.
			for (id_t wid : screens[sid].widgets) {

				Widget* widget = screen->addWidget(wid, widgets[wid].type, widgets[wid].position, widgets[wid].dimension, widgets[wid].refresh);
				if (not widget) {
					// Ignore when the widget type is not supported by the plugin.
					LOG(Logger::DEBUG, "Widget " + std::to_string(wid) + " ignored");
					continue;
				}

				// Custom parameters.
				for (auto& parameter : widgets[wid].parameters)
					widget->updateAttribute(parameter.first, parameter.second);

				// Plugin loading.
				if (not widgets[wid].plugin.empty()) {

					InputPluginHandler* inputPluginHandler = nullptr;
					if (inputPluginNames.find(widgets[wid].plugin) == inputPluginNames.end()) {
						// Create the input plugin handler.
						inputPluginHandler = new InputPluginHandler(widgets[wid].plugin, iPath);
						inputPluginHandler->initialize();
						inputPluginHandlers.push_back(inputPluginHandler);
						inputPluginNames.emplace(widgets[wid].plugin, inputPluginHandler);
					}
					else {
						// Use the existing one.
						inputPluginHandler = inputPluginNames[widgets[wid].plugin];
					}

					// Set input plugin functions (need to be before any refresh check).
					InputPlugin* inputPlugin = inputPluginHandler->getPlugin();
					RequestData requestData(
						widgets[wid].function,
						widgets[wid].subFunction,
						widgets[wid].data,
						widgets[wid].symbol
					);
					Request request(widget, inputPluginHandler, requestData);
					widget->setValue(inputPluginHandler->registerFunction(requestData));

					// Verify that the max refresh rate on the widget is correct.
					if (uint64_t maximunAcceptedRefresh = inputPluginHandler->getMaximunRefresh(widgets[wid].function, widgets[wid].subFunction)) {
						if (widgets[wid].refresh > maximunAcceptedRefresh) {
							LOG(Logger::WARNING, "The refresh rate on the widget " + std::to_string(wid) + " from screen " + std::to_string(sid) + " is too high (" + std::to_string(widgets[wid].refresh) + ") and got changed to " + std::to_string(maximunAcceptedRefresh));
							widget->changeInterval(maximunAcceptedRefresh);
							widgets[wid].refresh = maximunAcceptedRefresh;
						}
					}
					// If max is 0 then never refresh.
					else {
						widgets[wid].refresh = 0;
					}

					if (widgets[wid].refresh) {
						// Verify that the min refresh rate on the widget is correct.
						uint64_t minimunAcceptedRefresh = inputPluginHandler->getMinimunRefresh(widgets[wid].function, widgets[wid].subFunction);
						if (widgets[wid].refresh < minimunAcceptedRefresh) {
							LOG(Logger::WARNING, "The refresh rate on the widget " + std::to_string(wid) + " from screen " + std::to_string(sid) + " is too low (" + std::to_string(widgets[wid].refresh) + ") and got changed to " + std::to_string(minimunAcceptedRefresh));
							widget->changeInterval(minimunAcceptedRefresh);
							widgets[wid].refresh = minimunAcceptedRefresh;
						}

						// Create refresh work.
						refreshWork[outputPluginData.name][sid].push_back(request);
					}

					// First update ever, and the last one for many.
					inputPlugin->update(requestData, true);
				}
				// Static value widgets.
				else {
					widget->setFinal();
					LCDSpicer2::Value* value = new LCDSpicer2::Value;
					widget->setValue(value);
					value->set(widgets[wid].data);
				}
			}
			if (not screen->getWidgetIds().size()) {
				throw LCDError("No widgets to display for screen " + std::to_string(sid) + " on plugin " + outputPluginHandler->getName());
			}
			else {
				LOG(Logger::DEBUG, "Screen " + std::to_string(sid) + " with " + std::to_string(screen->getWidgetIds().size()) + " widgets loaded for plugin " + outputPluginHandler->getName());
			}
		}

		if (not screens.size())
			throw LCDError("No screens to display for plugin " + outputPluginHandler->getName());
		else
			LOG(Logger::DEBUG, std::to_string(outputPlugin->getScreenIds().size()) + " screens loaded for plugin " + outputPluginHandler->getName());

		// Set handler properties.
		Rotation screenRotation(outputPluginData.cycle, outputPluginData.direction);
		outputPluginHandler->setScreenRotation(screenRotation);
//		outputPluginHandler->setFirstScreen(outputPluginData.firstScreen);
	}

	// Release some memory.
	outputPlugins.shrink_to_fit();
	inputPluginHandlers.shrink_to_fit();

	return std::move(outputPlugins);
}

vector<OutputPluginData> DataLoader::processOutputNode() {

	vector<OutputPluginData> outputPluginDatas;
	umap<string, LCDValue> tempAttributes;
	vector<string> nodeAttributes = {
		"Plugin", "Cycle", "Direction", "Screens"
	};

	XMLElement* outputs = root->FirstChildElement("Outputs");
	if (not outputs)
		throw LCDError("Missing Outputs section.");

	XMLElement* element = outputs->FirstChildElement("Output");
	if (not element)
		throw LCDError("No Outputs found");

	for (; element; element = element->NextSiblingElement("Output")) {

		tempAttributes = processNode(element);
		if (not checkAttributes(nodeAttributes, tempAttributes))
			throw LCDError("Missing attributes in node Screens");

		OutputPluginData outputPluginData;

		outputPluginData.name = tempAttributes["Plugin"].getString();

		outputPluginData.cycle = tempAttributes["Cycle"].getInt();
		if (not Rotation::isValid(outputPluginData.cycle))
			throw LCDError("Invalid cycle selected");

		outputPluginData.direction = tempAttributes["Direction"].getInt();
		if (not Direction::isValid(outputPluginData.direction))
			throw LCDError("Invalid cycle direction selected");

		for (string screen : Explode(tempAttributes["Screens"].getString(), ',')) {
			int tempNumber;
			try {
				tempNumber = std::stoi(screen);
			}
			catch (...) {
				throw LCDError("Invalid screen Id for output plugin");
			}
			outputPluginData.screens.push_back(tempNumber);
		}

		outputPluginDatas.push_back(outputPluginData);
	}

	LOG(Logger::DEBUG, string("Found ") + std::to_string(outputPluginDatas.size()) + " Output Plugins");

	return std::move(outputPluginDatas);
}

umap<id_t, ScreenData> DataLoader::processScreenNode() {

	umap<id_t, ScreenData> screenDatas;
	id_t id;
	umap<string, LCDValue> tempAttributes;
	vector<string> nodeAttributes = {
		"Id", "Duration", "Widgets"
	};

	XMLElement* screens = root->FirstChildElement("Screens");
	if (not screens)
		throw LCDError("Missing Screens section.");

	XMLElement* element = screens->FirstChildElement("Screen");
	if (not element)
		throw LCDError("No screens found");
	for (; element; element = element->NextSiblingElement()) {

		tempAttributes = processNode(element);
		if (not checkAttributes(nodeAttributes, tempAttributes))
			throw LCDError("Missing attributes in node Screens");

		id = tempAttributes["Id"].getUInt();

		if (screenDatas.find(id) != screenDatas.end()) {
			LOG(Logger::WARNING, "Screen id " + std::to_string(id) + " already exist, ignored!");
			continue;
		}

		ScreenData screenData;

		screenData.duration = tempAttributes["Duration"].getInt();

		for (string widget : Explode(tempAttributes["Widgets"].getString(), ',')) {
			int tempNumber;
			try {
				tempNumber = std::stoi(widget);
			}
			catch (...) {
				throw LCDError("Invalid widget Id for screen");
			}
			screenData.widgets.push_back(tempNumber);
		}

		// Custom parameters.
		XMLElement* parameters = element->FirstChildElement("Parameters");
		if (not parameters)
			throw LCDError("Missing parameters node in screen");
		screenData.parameters = processNode(parameters);

		screenDatas[id] = std::move(screenData);
	}

	if (not screenDatas.size())
		throw LCDError("No screens found");
	else
		LOG(Logger::DEBUG, string("Found ") + std::to_string(screenDatas.size()) + " screens");

	return std::move(screenDatas);
}

umap<id_t, WidgetData> DataLoader::processWidgetNode() {

	umap<id_t, WidgetData> widgetDatas;
	umap<string, LCDValue> tempAttributes;
	vector<string> nodeAttributes = {
		"Id", "X", "Y", "Width",
		"Height", "Type", "Symbol", "Plugin",
		"Function", "SubFunction", "Data", "Refresh"
	};
	id_t id;

	XMLElement* widgets = root->FirstChildElement("Widgets");
	if (not widgets)
		throw LCDError("No widgets found");

	XMLElement* element = widgets->FirstChildElement("Widget");
	if (not element)
		throw LCDError("Unable to find the Widgets node");
	for (; element; element = element->NextSiblingElement("Widget")) {

		tempAttributes = processNode(element);
		if (not checkAttributes(nodeAttributes, tempAttributes))
			throw LCDError("Missing attributes in node Widgets");

		id = tempAttributes["Id"].getInt();

		if (widgetDatas.find(id) != widgetDatas.end()) {
			LOG(Logger::WARNING, "Widget id " + std::to_string(id) + " already exist, ignored!");
			continue;
		}

		WidgetData widgetData;
		// Positional information.
		widgetData.position.setX(tempAttributes["X"].getUInt());
		widgetData.position.setY(tempAttributes["Y"].getUInt());
		widgetData.dimension.setWidth(tempAttributes["Width"].getUInt());
		widgetData.dimension.setHeight(tempAttributes["Height"].getUInt());

		// Functional information.
		widgetData.type        = tempAttributes["Type"].getUInt();
		if (not Widget::isValid(widgetData.type))
			throw LCDError("Invalid widget type");
		widgetData.symbol      = tempAttributes["Symbol"].getInt();
		widgetData.plugin      = std::move(tempAttributes["Plugin"].getString());
		widgetData.function    = tempAttributes["Function"].getUInt();
		widgetData.subFunction = tempAttributes["SubFunction"].getUInt();
		widgetData.data        = std::move(tempAttributes["Data"].getString());
		widgetData.refresh     = tempAttributes["Refresh"].getUInt();

		// Custom parameters.
		XMLElement* parameters = element->FirstChildElement("Parameters");
		widgetData.parameters = processNode(parameters);
		widgetDatas[id] = std::move(widgetData);
	}

	if (not widgetDatas.size())
		throw LCDError("No widgets found");
	else
		LOG(Logger::DEBUG, "Found " + std::to_string(widgetDatas.size()) + " widgets");

	return std::move(widgetDatas);
}

