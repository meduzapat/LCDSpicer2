/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Screen.hpp
 * @ingroup		outputPlugins
 * @since		Oct 31, 2015
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

#ifndef SRC_LIBS_OUTPUTPLUGIN_SCREEN_HPP_
#define SRC_LIBS_OUTPUTPLUGIN_SCREEN_HPP_ 1

// To handle unordered map.
#include <unordered_map>

#include "Widget.hpp"

namespace LCDSpicer2 {

/**
 * LCDSpicer2::Screen.
 *
 * Defines an abstract object of type screen as base for any screen.
 */
class Screen : public Refresh {

public:

	/**
	 * Creates a new Screen.
	 *
	 * @param seconds the number of seconds this screen need to be displayed.
	 */
	Screen(const uint64_t seconds) : Refresh(seconds * TIMES_PER_SECOND) {};

	/**
	 * Clean up.
	 */
	virtual ~Screen();

	/**
	 * Updates an attribute on this screen with the information in value.
	 * Nothing happens if the attribute doens't exists.
	 *
	 * @param[in] attributeName what to change
	 * @param[in] value to what.
	 */
	virtual void update(const string& attributeName, Value& value) final;

	/**
	 * Turns this screen ON/OFF.
	 */
	void toggleScreen();

	/**
	 * Creates a new widget inside the screen.
	 *
	 * @param id the id of the new created widget.
	 * @param type the widget type.
	 * @param position the X Y coordinates where the widget will be located.
	 * @param dimension the width and height of the widget.
	 * @param ticks the number of ticks until the next update.
	 * @return a pointer to the new created widget.
	 */
	virtual Widget* addWidget(id_t id, parameter_t type, Position& position, Dimension& dimension, uint64_t ticks) final;

	/**
	 * Retrieves a list of widgets.
	 *
	 * @return a vector with the id of the widgets.
	 */
	virtual const vector<id_t> getWidgetIds() const final;

	/**
	 * This method is called to refresh the screen elements and request a redraw.
	 */
	void refresh();

	/**
	 * Verify if the screen needs a refresh.
	 *
	 * @return true if the screen needs a refresh.
	 */
	virtual bool isDirty() final;

	/**
	 * Sets the dirty state on this screen.
	 */
	virtual void setDirty() final;

	/**
	 * Returns a list of supported widgets with their specifications.
	 *
	 * @return a name > specification widget list.
	 */
	virtual umap<id_t, Specification> getSpecifications() = 0;

protected:

	/// Flag to report that a refresh is needed.
	bool dirty = true;

	 /// Flag to know if this screen is been displayed.
	bool displaying = false;

	/// Pointers to the widgets this screen holds.
	umap<id_t, Widget*> widgets;

	/// Vector with the function calls mapped to a string name.
	umap<string, std::function<void(Value&)>> functions;

	/**
	 * Creates a new widget.
	 *
	 * @param type a LCDSpicer widget
	 * @param position the X Y coordinates where the widget will be located.
	 * @param dimension the width and height of the widget.
	 * @param ticks the number of ticks.
	 * @return a pointer to the new Widget
	 */
	virtual Widget* createWidget(parameter_t type, Position& position, Dimension& dimension, uint64_t ticks) = 0;

	/**
	 * This function will be called when the screen gets refreshed to redraw it.
	 */
	virtual void redraw() = 0;

	/**
	 * Turns the screen off.
	 */
	virtual void turnOff() = 0;

	/**
	 * Turns the screen online.
	 */
	virtual void turnOn() = 0;

	/**
	 * Register a function to a name so it can be called.
	 *
	 * @param name the name to assign to the function call.
	 * @param function pointer to the function to call.
	 */
	virtual void registerFunction(string name, std::function<void (Value&)> function) final;

};

}

#endif /* SRC_LIBS_OUTPUTPLUGIN_SCREEN_HPP_ */
