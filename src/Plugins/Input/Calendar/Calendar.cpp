/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Calendar.cpp
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

#include "Calendar.hpp"

// Plugin factory functions.
#ifdef inputPluginFactory
	inputPluginFactory(Calendar)
#else
	#error "Plugin factory function missing."
#endif

bool Calendar::initialize() {

	return true;
}

LCDSpicer2::Value Calendar::processRequest(const LCDSpicer2::RequestData& requestData) {

	LCDSpicer2::Value value;
	std::time_t rawtime;
	std::tm* timeinfo;
	std::time(&rawtime);
	timeinfo = std::localtime(&rawtime);

	switch (requestData.subFunction) {

	case TEXTUAL_TIME: {

		string timeFormat;
		if (requestData.data.empty())
			timeFormat = "%T";
		else
			timeFormat = requestData.data;
		char buffer[DEFAULT_TEXTUAL_STRING_SIZE];

		std::strftime(buffer, DEFAULT_TEXTUAL_STRING_SIZE, timeFormat.c_str(), timeinfo);
		value.set(buffer);
		break;
	}
	// TODO data can be used to pass the locale.
	case RAW_TIME:
		value.set(timeinfo);
		break;
	}

	return value;
}

void Calendar::detectFunctionsValues(callBack_t callBack) {
	callBack(1, TEXTUAL_TIME, {
		{"Time 12",				"%r"},
		{"Time 24",				"%T"},
		{"Date short",			"%D"},
		{"Time long",			"%a %b #e Y"},
		{"Date and time short",	"%D %T"},
		{"Date and time long",	"%c"},
	});
};
