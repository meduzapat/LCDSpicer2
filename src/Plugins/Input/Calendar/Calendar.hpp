/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Calendar.hpp
 * @ingroup		inputPlugins
 * @since		Jan 13, 2016
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

#ifndef SRC_PLUGINS_INPUT_CALENDAR_CALENDAR_HPP_
#define SRC_PLUGINS_INPUT_CALENDAR_CALENDAR_HPP_

#include "InputPlugin.hpp"

using LCDSpicer2::Value;

#define TEXTUAL_TIME	1
#define RAW_TIME		2

#define DEFAULT_TEXTUAL_STRING_SIZE 80

/**
 * LCDSpicer2::Calendar
 */
class Calendar: public LCDSpicer2::InputPlugin {

public:

	bool initialize();

	void detectFunctionsValues(callBack_t callBack);

protected:

	/**
	 * Process the request.
	 *
	 * @param requestData
	 */
	Value processRequest(const LCDSpicer2::RequestData& requestData);
};


#endif /* SRC_PLUGINS_INPUT_CALENDAR_CALENDAR_HPP_ */
