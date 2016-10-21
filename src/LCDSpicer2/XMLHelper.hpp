/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		XMLHelper.hpp
 * @ingroup		LCDSpicer2
 * @since		Aug 19, 2016
 * @author		Patricio A. Rossi (MeduZa)
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

#ifndef SRC_LCDSPICER2_XMLHELPER_HPP_
#define SRC_LCDSPICER2_XMLHELPER_HPP_ 1

#include "Definitions.hpp"

// To process XML files.
#include <tinyxml2.h>
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;

using std::string;
using std::vector;

namespace LCDSpicer2 {

// Conflicting with tinyxml2 Error function
using LCDError = LCDSpicer2::Error;
// Conflicting with tinyxml2 Error function
using LCDValue = LCDSpicer2::Value;

/**
 * LCDSpicer2::XMLHelper
 *
 * This class wraps over the tinyxml2 class and adds LCDSpicer functionality.
 */
class XMLHelper : protected XMLDocument {

public:

	/**
	 * Creates a new XMLHelper object and open the XML file.
	 *
	 * @param fileName
	 * @throws LCDSpicer::Error if the file is missing, the body is missing or the version is different.
	 */
	XMLHelper(const string& fileName);

	/**
	 * Reads the attributes from a XML node.
	 *
	 * @param parentElement
	 * @param nodeName
	 * @return A map with the key pairs.
	 * @throws Error if an error happen.
	 */
	umap<string, LCDValue> processNode(XMLElement* nodeElement);

	/**
	 * Reads the attributes from a node by its name.
	 *
	 * @param nodeName The name of the node, note that only the first occurence will be read.
	 * @return A map with the parameters in that node.
	 * @throws Error if node does not exist or an error happen.
	 */
	umap<string, LCDValue> processNode(const string& nodeName);

	/**
	 * Checks if the map subject have the attributeList elements.
	 * This function ignores other elements.
	 *
	 * @param attributeList A list of attributes to check.
	 * @param subjects A map to check.
	 * @return true if all attributes exists on the subject map.
	 */
	bool checkAttributes(const vector<string>& attributeList, umap<string, LCDValue>& subjects);

protected:

	/**
	 * Pointer to the root element.
	 */
	XMLElement* root = nullptr;

};

}

#endif /* SRC_LCDSPICER2_XMLHELPER_HPP_ */
