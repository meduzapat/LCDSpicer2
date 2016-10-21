/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		XMLHelper.cpp
 * @ingroup
 * @since		Aug 19, 2016
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
#include "XMLHelper.hpp"

using namespace LCDSpicer2;

XMLHelper::XMLHelper(const string& fileName) {

	if (LoadFile(fileName.c_str()) != tinyxml2::XML_NO_ERROR)
		throw LCDError("Unable to read the file " + fileName);

	root = RootElement();
	if (not root or string(root->Name()) != "LCDSpicer")
		throw LCDError("Unknown data file");

	if (root->Attribute("Version") and string(root->Attribute("Version")) != DataDocumentVersion)
		throw LCDError("Invalid data file version");
}

umap<string, LCDValue> XMLHelper::processNode(XMLElement* nodeElement) {

	umap<string, LCDValue> groupValues;

	const XMLAttribute* pAttrib = nodeElement->FirstAttribute();

	while (pAttrib) {
		LCDValue value;

		int intVal = 0;
		double floatVal = 0.00;

		value.set(pAttrib->Value());

		groupValues.emplace(pAttrib->Name(), value);
		pAttrib = pAttrib->Next();
	}

	return std::move(groupValues);
}

umap<string, LCDValue> XMLHelper::processNode(const string& nodeElement) {

	XMLElement* node = root->FirstChildElement(nodeElement.c_str());
	if (not node)
		throw LCDError("Missing " + nodeElement + " section.");

	return std::move(processNode(node));
}

bool XMLHelper::checkAttributes(const vector<string>& attributeList, umap<string, LCDValue>& subjects) {

	for (string attribute : attributeList) {
		if (subjects.find(attribute) == subjects.end())
			return false;
	}

	return true;
}
