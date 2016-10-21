/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		GenericFunctions.cpp
 * @ingroup		general
 * @author		Patricio A. Rossi (MeduZa)
 * @date		Oct 27, 2015
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

#include <GenericFunctions.hpp>

// to read directories.
#include<dirent.h>

void LCDSpicer2::ltrim(string& text) {
	size_t chars = 0;
	for (size_t c = 0; c < text.size(); c++) {
		if (text[c] != ' ' and text[c] != '\n' and text[c] != '\t')
			break;
		chars ++;
	}
	if (chars)
		text.erase(0,chars);
}

void LCDSpicer2::rtrim(string& text) {
	size_t chars = 0;
	for (size_t c = text.size(); c > 0; c--) {
		if (text[c] != ' ' and c != '\n' and c != '\t')
			break;
		chars ++;
	}
	if (chars)
		text.resize(text.size() - chars + 1);
}

void LCDSpicer2::trim(string& text) {
	ltrim(text);
	rtrim(text);
}

vector<string> LCDSpicer2::Explode(const string& text, const char delimiter, const size_t limit) {

	vector<string> temp;

	size_t start = 0, end = 0;

	for (size_t c = 0; limit ? c < limit : true; c++) {
		end = text.find(delimiter, start);
		if (end == string::npos) {
			temp.push_back(text.substr(start));
			return std::move(temp);
		}
		temp.push_back(text.substr(start, end - start));
		start = end + 1;
	}

	return std::move(temp);
}

bool LCDSpicer2::inVector(const string& needle, const vector<string>& haystack) {
	for (string element : haystack)
		if (element == needle)
			return true;
	return false;
}

string LCDSpicer2::AlignText(const string& text, uint8_t alignment, uint8_t width, string* leftSpace, string* rightSpace) {

	string addRight, addLeft;
	uint8_t size = text.size();

	if (size >= width) {
		if (leftSpace != nullptr)
			leftSpace->clear();

		if (rightSpace != nullptr)
			rightSpace->clear();

		return text;
	}

	uint8_t diff = width - size;

	switch (alignment) {
	case 0: // ALIGN_LEFT
		addRight.append(diff, ' ');
		break;

	case 1: // ALIGN_RIGHT
		addLeft.append(diff, ' ');
		break;

	case 2: // ALIGN_CENTER
		addLeft.append(diff / 2, ' ');
		addRight.append((diff / 2) + (diff % 2), ' ');
	}

	if (leftSpace != nullptr)
		*leftSpace = addLeft;

	if (rightSpace != nullptr)
		*rightSpace = addRight;

	return (addLeft + text + addRight);
}

vector<string> LCDSpicer2::getDirectoryFiles(const string& path) {
	vector<string> files;
	string file;
	DIR *pDIR = opendir(path.c_str());
	if (pDIR == nullptr)
		throw "Unable to open the directory";

	while (dirent *entry = readdir(pDIR)) {
		file = entry->d_name;
		if (file != "." and file != ".." and entry->d_type == DT_REG)
			files.push_back(file);
	}
	closedir(pDIR);
	return std::move(files);
}
