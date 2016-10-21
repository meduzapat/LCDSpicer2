/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Users.hpp
 * @ingroup		inputPlugins
 * @since		Nov 29, 2015
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

#ifndef SRC_PLUGINS_INPUT_USERS_USERS_HPP_
#define SRC_PLUGINS_INPUT_USERS_USERS_HPP_ 1

#include "InputPlugin.hpp"

using namespace LCDSpicer2;

#define USER		1
#define USERS		2
#define USER_COUNT	3
#define USERS_COUNT	4

/**
 * LCDSpicer2::Users
 *
 * Plugin to return logged users information.
 */
class Users: public InputPlugin {

public:

	bool initialize();

	void detectFunctionsValues(callBack_t callBack) {};

protected:

	/**
	 * Stores the current user name.
	 */
	string currentUserName;

	/**
	 * Keeps a list of logged users.
	 */
	umap<string, uint> users;

	Value processRequest(const RequestData& requestData);

	/**
	 * Returns the list of users.
	 */
	void getUsersList();
};

#endif /* SRC_PLUGINS_INPUT_USERS_USERS_HPP_ */
