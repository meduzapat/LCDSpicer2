/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Widget.hpp
 * @ingroup		outputPlugins
 * @since		Mar 10, 2014
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

#ifndef SRC_LIBS_OUTPUTPLUGIN_WIDGET_HPP_
#define SRC_LIBS_OUTPUTPLUGIN_WIDGET_HPP_ 1

#define BIND(functionName) std::bind(&functionName, this, _1)

// To handle unordered map.
#include <unordered_map>

#include <array>
using std::array;

#include <functional>
using namespace std::placeholders;

#include "OutputDefinitions.hpp"
#include "Refresh.hpp"

namespace LCDSpicer2 {

/**
 * Widget model (interface)
 */
class Widget : public Position, public Dimension, public Refresh {

public:

	/**
	 * @}
	 * @defgroup widgets Widgets types handled by LCDSpicer.
	 * @{
	 */

	/**
	 * A simple readable text element.
	 *
	 * Can display any kind of alphanumeric data in many different ways.
	 */
	static constexpr uint8_t TEXT	= 0;

	/**
	 * Displays a 2D percentage bar.
	 *
	 * Bars are widgets that can display a percentage using a graphical progress bar.
	 */
	static constexpr uint8_t BAR	= 1;

	/**
	 * A small graphical element on the screen.
	 *
	 * An icon is a character size element,
	 * normally used on non graphical screens to display some fancy elements,
	 * for real graphical icons on a graphical aware hardware use a WIDGET_BITMAP.
	 */
	static constexpr uint8_t ICON	= 2;

	/**
	 * Image or animation of some kind.
	 *
	 * Only used by hardware that support bitmaps,
	 * defines a section of the screen where a image will be displayed.
	 * @note Only available on graphical hardware
	 */
	static constexpr uint8_t BITMAP	= 3;

	//static const parameter_t CHART	= 4;

	/**
	 * A clock that represent time and date.
	 *
	 * Feed with time information will display the date and time information.
	 */
	static constexpr uint8_t CLOCK	= 5;
	 /// @}

	/// Widget types labels.
	static const array<const char*, 6> WIDGETS;

	/**
	 * Creates a new widget with the position and dimension.
	 *
	 * @param position
	 * @param dimension
	 * @param ticks the refresh time.
	 */
	Widget(Position& position, Dimension& dimension, uint64_t ticks = 0) :
		Position(position.getX(), position.getY()),
		Dimension(dimension.getWidth(), dimension.getHeight()),
		Refresh(ticks) {};

	/**
	 * Clean up.
	 */
	virtual ~Widget();

	/**
	 * Checks for the correct widget type.
	 *
	 * @note It only include basic and supported types.
	 */
	static bool isValid(uint8_t widget);

	/**
	 * Returns the Widget Type
	 * @return the widget type code.
	 */
	virtual uint8_t getType() = 0;

	/**
	 * Updates an attribute on the widget.
	 *
	 * @param attributeName the attribute name.
	 * @param value the new value for the attribute.
	 */
	virtual void updateAttribute(const string& attributeName, Value& value) final;

	/**
	 * Sets the final flag to true.
	 */
	virtual void setFinal() final;

	/**
	 * Checks for final flag.
	 *
	 * @return true if the widget value is final.
	 */
	virtual bool isFinal() final;

	/**
	 * Call to redraw the widget position, dimension and value on the screen.
	 */
	void refresh();

	/**
	 * Verify if the widget needs a refresh.
	 *
	 * @return true if the widget needs a refresh.
	 */
	virtual bool isDirty() final;

	/**
	 * Sets the dirty state on this widget.
	 */
	virtual void setDirty() final;

	/**
	 * Points to the value.
	 *
	 * @param value pointer to the value.
	 */
	virtual void setValue(Value* const value) final;

	/**
	 * Return a pointer to the internal value.
	 *
	 * @return a pointer.
	 */
	virtual Value* const getValue() final;

	/**
	 * Returns the widget specifications.
	 *
	 * @return a structure with the widget specifications.
	 */
	virtual Specification getSpecification();

protected:

	/// Flag to report that a refresh is needed.
	bool dirty = true;

	/**
	 * Register a function to a name so it can be called.
	 *
	 * @param name the name to assign to the function call.
	 * @param function pointer to the function to call.
	 */
	virtual void registerFunction(string name, std::function<void (Value&)> function) final;

	/**
	 * Method to redraw the widget.
	 */
	virtual void redraw() = 0;

private:

	/// Value this widget will display (if any).
	Value* value = nullptr;

	/// Keeps the last Value foot print.
	uint64_t lastValueFootPrint = 0;

	 /// Vector with the function calls mapped to a string name.
	umap<string, std::function<void(Value&)>> functions;

	/// If the this flag is set, the plugin value is final, it never changes.
	bool final = false;
};

}

#endif /* SRC_LIBS_OUTPUTPLUGIN_WIDGET_HPP_ */
