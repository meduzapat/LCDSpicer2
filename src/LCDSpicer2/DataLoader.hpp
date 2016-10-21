/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		DataLoader.hpp
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

#ifndef SRC_LCDSPICER2_DATALOADER_HPP_
#define SRC_LCDSPICER2_DATALOADER_HPP_

// To process XML files.
#include "XMLHelper.hpp"

#include "Request.hpp"
#include "Direction.hpp"
#include "Position.hpp"

namespace LCDSpicer2 {

/**
 * Used to extract information from the data file.
 */
struct OutputPluginData {
	string			name		= "";
	parameter_t		cycle		= 0;
	parameter_t		direction	= 0;
	vector<id_t>	screens;
};

/**
 * Used to extract information from the data file.
 */
struct ScreenData {
	uint64_t				duration	= 0;
	vector<id_t>			widgets;
	umap<string, LCDValue>	parameters;
};

/**
 * Used to extract information from the data file.
 */
struct WidgetData {
	Position				position;
	Dimension				dimension;
	parameter_t				type		= 0;
	string					plugin		= "";
	id_t					function	= 0;
	id_t					subFunction	= 0;
	string					data		= "";
	int16_t					refresh		= 0;
	umap<string, LCDValue>	parameters;
	int16_t					symbol		= -1;
};

/**
 * DataLoader.
 *
 * This class loads a data file and creates every plugin an object needs to run the program.
 */
class DataLoader : protected XMLHelper {

public:

	/**
	 * Creates a new DataLoader using the fileName file.
	 *
	 * @param fileName the file to load.
	 * @throws LCDSpicer2::Error
	 */
	DataLoader(const string& fileName);

	/**
	 * Returns the list of detected input plugin handlers.
	 *
	 * @return the return value will be moved.
	 */
	vector<InputPluginHandler*> getInputPluginHandlers();

	/**
	 * Process the configuration from the data file.
	 *
	 * @return Returns a vector of OutputPluginHandlers.
	 * @throws LCDSpicer2::Error
	 */
	vector<OutputPluginHandler*> getOutputPluginHandlers();


	/**
	 * Returns the detected request work list by output plugin.
	 *
	 * @return the value will be moved.
	 */
	umap<string, umap<id_t, vector<Request>>> getRefreshWork();

	virtual ~DataLoader() {};

protected:

	/// To log stuff.
	static Logger* logger;

	/// Stores the refresh work.
	umap<string, umap<id_t, vector<Request>>> refreshWork;

	/// Keeps the detected input plugin handlers.
	vector<InputPluginHandler*> inputPluginHandlers;

	/**
	 * Reads and process the output node.
	 *
	 * @return a vector that holds the output plugins data.
	 * @throws LCDSpicer2::Error
	 */
	inline vector<OutputPluginData> processOutputNode();

	/**
	 * Reads and process the screens node.
	 *
	 * @return a vector that holds the screens data.
	 * @throws LCDSpicer2::Error
	 */
	inline umap<id_t, ScreenData> processScreenNode();

	/**
	 * Reads and process the widget node.
	 *
	 * @return a vector that holds the widget data.
	 * @throws LCDSpicer2::Error
	 */
	inline umap<id_t, WidgetData> processWidgetNode();

};

}

#endif /* SRC_LCDSPICER2_DATALOADER_HPP_ */
