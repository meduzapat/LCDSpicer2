/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		InputPluginManifest.cpp
 * @ingroup
 * @since		Feb 24, 2016
 * @author		Patricio A. Rossi (MeduZa)
 * @copyright	Copyright © 2015 Patricio A. Rossi (MeduZa)
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

#include "InputPluginManifest.hpp"

using namespace LCDSpicer2;

void InputPluginManifest::readManifest(bool fullExtraction) {

	functions.clear();
	umap<string, LCDValue> tempAttributes;
	umap<string, LCDValue> tempSubAttributes;
	vector<string> nodeAttributes    = {"Id"};
	vector<string> nodeSubAttributes = {
		"Id", "MinimumRefresh", "MaximumRefresh",
		"AcceptCustomValues", "DataType"
	};
	if (fullExtraction) {
		nodeAttributes.push_back("Name");
		nodeSubAttributes.push_back("Name");
		nodeSubAttributes.push_back("Description");
		nodeSubAttributes.push_back("SymbolType");
		nodeSubAttributes.push_back("Image");
	}

	XMLElement* functions = root->FirstChildElement("Functions");
	if (not functions)
		throw LCDSpicer2::Error("Missing functions section.");

	XMLElement* function = functions->FirstChildElement("Function");
	if (not function)
		throw LCDSpicer2::Error("Empty functions node.");

	for (; function; function = function->NextSiblingElement("Function")) {

		tempAttributes = processNode(function);
		if (not checkAttributes(nodeAttributes, tempAttributes))
			throw LCDError("Missing attributes in node Function");

		Function functionData;

		// Extract function id.
		id_t functionId = tempAttributes["Id"].getUInt();
		if (not functionId)
			throw LCDError("Missing or empty function Id.");

		// Extract function name.
		if (fullExtraction) {
			functionData.name = tempAttributes["Name"].getString();
			if (functionData.name.empty())
				throw LCDError("Missing or empty function name.");
		}

		// Process sub functions.
		XMLElement* subFunction = function->FirstChildElement("SubFunction");
		if (not subFunction)
			throw LCDError("Empty sub functions node.");

		for (; subFunction; subFunction = subFunction->NextSiblingElement("SubFunction")) {

			tempSubAttributes = processNode(subFunction);
			if (not checkAttributes(nodeSubAttributes, tempSubAttributes))
				throw LCDError("Missing attributes in node subFunction");

			SubFunction subFunctionData;

			// Extract sub function id.
			id_t subFunctionId = tempSubAttributes["Id"].getUInt();
			if (not subFunctionId)
				throw LCDError("Missing or empty subFunction Id.");

			// Extract sub minimum refresh rate.
			subFunctionData.minimunRefreshRate = tempSubAttributes["MinimumRefresh"].getUInt();

			// Extract sub maximum refresh rate.
			subFunctionData.maximunRefreshRate = tempSubAttributes["MaximumRefresh"].getUInt();

			// Extract sub function acceptCustomValues flag.
			subFunctionData.acceptCustomValues = (tempSubAttributes["AcceptCustomValues"].getUInt() == 1);

			// Extract sub function dataType bit.
			subFunctionData.dataType = tempSubAttributes["DataType"].getUInt();
			if (!isValidDataType(subFunctionData.dataType))
				throw LCDError("Invalid dataType");

			if (fullExtraction) {

				// Extract sub function name.
				subFunctionData.name = tempSubAttributes["Name"].getString();
				if (subFunctionData.name.empty())
					throw LCDError("Missing or empty sub function name.");

				// Extract sub function description.
				subFunctionData.description = tempSubAttributes["Description"].getString();
				if (subFunctionData.description.empty())
					throw LCDError("Missing or empty sub function description.");

				// Extract sub function symbol
				subFunctionData.symbolType = tempSubAttributes["SymbolType"].getString();

				// Extract sub function image.
				subFunctionData.image = tempSubAttributes["Image"].getString();
				if (subFunctionData.image.empty())
					throw LCDError("Missing or empty sub function image.");
			}

			functionData.subFunctions.emplace(subFunctionId, subFunctionData);
		}
		this->functions.emplace(functionId, functionData);
	}
}

umap<id_t, Function> InputPluginManifest::getFunctions(bool fullExtraction) {
	readManifest(fullExtraction);
	return functions;
}
