/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		InputPluginManifest.hpp
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

#ifndef SRC_LCDSPICER2_INPUTPLUGINMANIFEST_HPP_
#define SRC_LCDSPICER2_INPUTPLUGINMANIFEST_HPP_ 1

#include "../Libs/InputPlugin/InputDefinitions.hpp"
#include "PluginManifest.hpp"

namespace LCDSpicer2 {

/**
 * LCDSpicer2::InputPluginManifest
 */
class InputPluginManifest: public PluginManifest {

public:

	using PluginManifest::PluginManifest;

	umap<id_t, Function> getFunctions(bool fullExtraction);

protected:

	void readManifest(bool fullExtraction);

private:

	/**
	 * Stores the input plugin's functions.
	 */
	umap<id_t, Function> functions;

};

} /* namespace LCDSpicer2 */

#endif /* SRC_LCDSPICER2_INPUTPLUGINMANIFEST_HPP_ */
