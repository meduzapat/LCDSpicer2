/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		InputPlugin.hpp
 * @ingroup		inputPlugins
 * @since		Dec 17, 2013
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

#include "InputPlugin.hpp"

using namespace LCDSpicer2;

InputPlugin::~InputPlugin() {
	for (auto f : internalRefresh)
		delete f.second;
}

Value* InputPlugin::registerValue(id_t functionId, id_t subFunctionId,const string& data) {
	values[functionId][subFunctionId][data].set(0);
	return &values[functionId][subFunctionId][data];
}

void InputPlugin::update(RequestData& requestData, bool force) {

	if (force or internalRefresh[requestData.function]->isDue()) {
		requestData.setUpdate(true);
		internalRefresh[requestData.function]->mark();
	}

	values[requestData.function][requestData.subFunction][requestData.data] = processRequest(requestData);
	requestData.setUpdate(false);
}

void InputPlugin::setFunctionRefreshRate(id_t function, uint64_t newRefresh) {
	if (internalRefresh.find(function) == internalRefresh.end())
		internalRefresh.emplace(function, new Refresh(newRefresh));
}

bool RequestData::needUpdate() const {
	return functionIsDue;
}

void RequestData::setUpdate(bool update) {
	functionIsDue = update;
}
