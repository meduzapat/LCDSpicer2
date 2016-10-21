/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Error.hpp
 * @ingroup		general
 * @since		Nov 19, 2015
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
#ifndef SRC_LIBS_ERROR_HPP_
#define SRC_LIBS_ERROR_HPP_

#include <exception>
#include <string>
using std::string;

namespace LCDSpicer2 {

/**
 * LCDSpicer2::Error
 *
 * Class to handle exceptions.
 */
class Error: public std::exception {

public:

	/**
	 * Creates a new Error with a message using C style string.
	 *
	 * @param message
	 */
	Error(const char* message);

	/**
	 * Creates a new Error with a message using a string.
	 *
	 * @param message
	 */
	Error(const string& message);

	/**
	 * Creates a new Error with a message using a pointer to a string.
	 *
	 * @param message
	 */
	Error(const string* message);

	/**
	 * Clean up.
	 */
	virtual ~Error() {};

	/**
	 * Returns the error message.
	 *
	 * @return
	 */
	const char* what() const noexcept;

protected:

	/**
	 * Stores the error message.
	 */
	string message = "";

};

} /* namespace LCDSpicer2 */

#endif /* SRC_LIBS_ERROR_HPP_ */
