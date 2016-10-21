/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		InputTypes.hpp
 * @ingroup		inputPlugins
 * @since		Mar 5, 2014
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

#ifndef SRC_LCDSPICER2_INPUTDEFINITIONS_HPP_
#define SRC_LCDSPICER2_INPUTDEFINITIONS_HPP_ 1

#include "Definitions.hpp"

namespace LCDSpicer2 {

/**
 * Main structure to handle sub functions information.
 */
struct SubFunction {
	string					name;
	string					description;
	bool					acceptCustomValues = false;
	uint64_t				minimunRefreshRate = 0;
	uint64_t				maximunRefreshRate = 0;
	parameter_t				symbol = 0;
	parameter_t				dataType = DATA_STRING;
	umap<string, string>	values;
	string					symbolType;
	string					image;
};

/**
 * Main structure to handle functions information.
 */
struct Function {
	string					name;
	umap<id_t, SubFunction>	subFunctions;
};

/**
 * Structure to send request information to the input plugins.
 */
struct RequestData {

	RequestData(id_t function, id_t subFunction, const string& data, int16_t symbol) :
		function(function),
		subFunction(subFunction),
		data(data),
		symbol(symbol) {}

	/// The function we want to run on the plugin.
	const id_t function;

	/// Sub function Id.
	const id_t subFunction;

	/// Special requests.
	const string data;

	/**
	 *  If the value will be converted into any special symbol
	 *  Negative one (AUTO).
	 *  Zero display no symbol.
	 */
	int16_t symbol;

	/**
	 * returns true if the request need to be executed.
	 *
	 * @return true or false.
	 */
	bool needUpdate() const;

	/**
	 * Set the internal flag for updates.
	 *
	 * @param update The new flag value.
	 */
	void setUpdate(bool update);

protected:

	/// Flag to report that the function needs update.
	bool functionIsDue = false;
};

}

#endif /* SRC_LCDSPICER2_INPUTDEFINITIONS_HPP_ */
