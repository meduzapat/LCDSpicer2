/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Configuration.cpp
 * @ingroup		LCDSpicer2
 * @since		Oct 24, 2015
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

#include "Configuration.hpp"

using namespace LCDSpicer2;

umap<string, LCDValue> Configuration::getGroupSettings(const string& groupName) {

	XMLElement* from;
	if (groupName == "Main")
		from = root;
	else
		from = root->FirstChildElement("Plugins");

	XMLElement* node = from->FirstChildElement(groupName.c_str());
	if (not node)
		throw LCDError("Unable to find the node " + groupName);

	umap<string, LCDValue> groupValues = processNode(node);

	return std::move(groupValues);
}
