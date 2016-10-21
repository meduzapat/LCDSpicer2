/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Request.hpp
 * @ingroup		LCDSpicer2
 * @since		Jan 12, 2016
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
#ifndef SRC_LCDSPICER2_REQUEST_HPP_
#define SRC_LCDSPICER2_REQUEST_HPP_

#include "OutputPluginHandler.hpp"

#include "InputPluginHandler.hpp"

namespace LCDSpicer2 {

/**
 * LCDSpicer2::Request
 *
 * Class that handle work request for the input data.
 */
class Request {

public:

	/**
	 * Creates a new Request instance.
	 *
	 * @param widget target element to mark as updated.
	 * @param inputPluginHandler plugin providing the data.
	 * @param requestData the information that need to be refreshed.
	 */
	Request(Widget* widget, InputPluginHandler* inputPluginHandler, const RequestData& requestData) :
		widget(widget), inputPluginHandler(inputPluginHandler), requestData(std::move(requestData)) {}

	/**
	 * Clean up.
	 */
	virtual ~Request() {};

	/**
	 * Returns a pointer to the internal plugin.
	 *
	 * @return a pointer to the internal plugin.
	 */
	const InputPlugin*& getInputPlugin() const;

	/**
	 * Returns the function id.
	 *
	 * @return the function id.
	 */
	id_t getFunction() const;

	/**
	 * Returns the sub function id.
	 *
	 * @return the sub function id.
	 */
	id_t getSubFunction() const;

	/**
	 * Returns the extra data to pass to the function.
	 *
	 * @return a string with the information needed by the function.
	 */
	const string& getData() const;

	/**
	 * Do a refresh.
	 */
	void refresh();

private:

	/// Pointer to the input plugin handler that contains the plugin that satisfies this request.
	InputPluginHandler* inputPluginHandler = nullptr;

	/// Pointer to the widget that requested this work.
	Widget* widget = nullptr;

	/// Structure with the information needed to do a request.
	RequestData requestData;
};

} /* namespace LCDSpicer2 */

#endif /* SRC_LCDSPICER2_REQUEST_HPP_ */
