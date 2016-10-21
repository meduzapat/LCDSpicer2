/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Configuration.hpp
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

#ifndef SRC_LIBS_CONFIGURATION_HPP_
#define SRC_LIBS_CONFIGURATION_HPP_ 1

// To handle strings.
#include <string>
using std::string;
using std::to_string;

// To read config files.
#include "XMLHelper.hpp"

namespace LCDSpicer2 {

/**
 * Configuration.
 *
 * Class to read the configuration file.
 */
class Configuration : public XMLHelper {

public:

	/**
	 * Creates a new configuration object from the configurationFile.
	 *
	 * @param configurationFile
	 * @throw LCDSpicer2::Error if the file is missing or invalid.
	 */
	Configuration(const string& configurationFile) : XMLHelper(configurationFile) {};

	virtual ~Configuration() {};

	/**
	 * Gets the settings for the specific group name.
	 * If the group name is Main will return the configuration for the main program
	 * If not will return the configuration for a plugin.
	 *
	 * @param groupName The group to extract from.
	 * @return A map with the parameters and their values in pairs.
	 * @throws LCDSpicer2::Error if the node is not existing.
	 */
	umap<string, LCDValue> getGroupSettings(const string& groupName);
};

}

#endif /* SRC_LIBS_CONFIGURATION_HPP_ */
