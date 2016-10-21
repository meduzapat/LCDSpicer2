/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Users.cpp
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

// To get the current user ID
#include <unistd.h>
// To get current user and real user name
#include <pwd.h>
// To get users names
#include <utmpx.h>

#include "Users.hpp"

// Plugin factory functions.
#ifdef inputPluginFactory
	inputPluginFactory(Users)
#else
	#error "Plugin factory function missing."
#endif

bool Users::initialize() {
	passwd *p = getpwuid(getuid());
	currentUserName = p->pw_name;
	return true;
}

Value Users::processRequest(const LCDSpicer2::RequestData& requestData) {

	Value temp;

	switch (requestData.subFunction) {

	case USER:
		temp.set(currentUserName);
	break;

	case USERS: {

		if (requestData.needUpdate())
			getUsersList();

		string list;
		for (auto user : users)
			list.append(user.first + ",");

		list.resize(list.size() - 1);

		temp.set(list);
	}
	break;

	case USER_COUNT:

		if (requestData.needUpdate())
			getUsersList();

		temp.set(users[currentUserName]);
	break;

	case USERS_COUNT:

		if (requestData.needUpdate())
			getUsersList();

		temp.set(users.size());
	break;
	}
	return temp;
}

void Users::getUsersList() {

	utmpx *ut;
	users.clear();

	while ((ut = getutxent()) != NULL) {

		if (*ut->ut_user != '\0' and ut->ut_type == USER_PROCESS) {

			if (users.find(ut->ut_user) != users.end())
				users[ut->ut_user]++;
			else
				users[ut->ut_user] = 1;
		}
	}
	endutxent();
}

