/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		GenericFunctions.hpp
 * @ingroup		general
 * @date		Mar 21, 2014
 * @author		Patricio A. Rossi (MeduZa)
 *
 * @copyright 	Copyright © 2015 - 2016 Patricio A. Rossi (MeduZa)
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

#ifndef SRC_LIBS_GENERICFUNCTIONS_HPP_
#define SRC_LIBS_GENERICFUNCTIONS_HPP_ 1

// To use strings.
#include <string>
using std::string;

// To use vectors.
#include <vector>
using std::vector;

namespace LCDSpicer2 {

/**
 * Removes empty characters from the left of a string.
 *
 * @param[out] text
 */
void ltrim(string& text);

/**
 * Removes empty characters from the right of a string.
 *
 * @param[out] text
 */
void rtrim(string& text);

/**
 * Removes empty characters from both sides.
 *
 * @param[out] text
 */
void trim(string& text);

/**
 * Split an array into parts using a delimiter character.
 * @param[in] text with the elements to split.
 * @param delimiter The glue to use between elements.
 * @param limit (optional) stop after this number of elements (default 0 = until the infinite and beyond).
 * @return an array with the chucks.
 */
vector<string> Explode(	const string&	text,
						const char		delimiter,
						const size_t	limit = 0);

/**
 * Search needle inside the haystack.
 * @param needle the element to search for.
 * @param haystack the array where to search.
 * @return true if the element is present in the array.
 */
bool inVector(const string& needle, const vector<string>& haystack);

/**
 * Align text using spaces.
 *
 * @param text the text to align.
 * @param alignment the alignment @ref textAlignment
 * @param width the number of characters of space to align to.
 * @param leftSpace if not null will be set with the left spacing.
 * @param rightSpace if not null will be set with the right spacing.
 * @return the aligned text.
 */
string AlignText(const string& text, uint8_t alignment, uint8_t width, string* leftSpace = nullptr, string* rightSpace = nullptr);

/**
 * Reads the directory contents.
 *
 * @param path the directory to look into.
 * @return a list of directories.
 */
vector<string> getDirectoryFiles(const string& path);

}


#endif /* SRC_LIBS_GENERICFUNCTIONS_HPP_ */
