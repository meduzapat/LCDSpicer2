/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Plugin.cpp
 * @ingroup		plugins
 * @since		Mar 15, 2014
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

#include "Plugin.hpp"

using namespace LCDSpicer2;

Plugin::Plugin() {
	logger = Logger::getInstance();
}

const int Plugin::getApiVersion() {
	return PLUGIN_API_VERSION;
}

void Plugin::setConfiguration(umap<string, Value> configuration) {
	this->configuration = std::move(configuration);
}

bool Plugin::getConfigurationValue(const string& key, Value& value) {

	auto got = configuration.find(key);

	if (got == configuration.end())
		return false;

	value = std::move(Value(got->second));

	return true;
}

