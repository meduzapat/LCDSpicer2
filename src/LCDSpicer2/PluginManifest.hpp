/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		PluginManifest.hpp
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

#include "../Libs/InputPlugin/InputDefinitions.hpp"
#include "XMLHelper.hpp"

#ifndef SRC_LCDSPICER2_PLUGINMANIFEST_HPP_
#define SRC_LCDSPICER2_PLUGINMANIFEST_HPP_ 1

namespace LCDSpicer2 {

/**
 * LCDSpicer2::PluginManifest
 *
 * Interface for manifest files handling.
 */
class PluginManifest : protected XMLHelper {

public:

	/**
	 * Creates a new object opening the filename.
	 *
	 * @param fileName The manifest file in XML format to open
	 * @throws Error if the file is bad, not compatible or corrupted.
	 */
	PluginManifest(const string& fileName) : XMLHelper(fileName) {};

	/**
	 * clean up.
	 */
	virtual ~PluginManifest() {};

protected:

	/**
	 * Extracts the information from the xml file.
	 *
	 * @param fullExtraction set to true to do a full data extraction, needed for the GUIs.
	 * @throws Error if something is bad or missing.
	 */
	virtual void readManifest(bool fullExtraction = false) = 0;

};

} /* namespace LCDSpicer2 */

#endif /* SRC_LCDSPICER2_PLUGINMANIFEST_HPP_ */
