
#ifndef EXAMPLE_PLUGINS_OUTPUT_EXAMPLEOUTPUTPLUGIN_HPP_
#define EXAMPLE_PLUGINS_OUTPUT_EXAMPLEOUTPUTPLUGIN_HPP_ 1

#include "ExampleOutputPluginScreen.hpp"
#include "lcdspicer2/OutputPlugin.hpp"

/**
 * ExampleOutputPlugin.hpp
 *
 * ExampleOutputPlugin is an output plugin example.
 */
class ExampleOutputPlugin : public LCDSpicer2::OutputPlugin {

public:

	/**
	 * Write any clean up code here.
	 */
	virtual ~ExampleOutputPlugin();

	/**
	 * Write any initialization code here.
	 *
	 * @return the status code for initialization
	 */
	bool initialize();

	/**
	 * Refresh everything that need refresh and return a status code.
	 *
	 * @return
	 */
	uint8_t refresh();

	/**
	 * Creates a ExampleOutputPlugin Screen
	 *
	 * @param seconds number of seconds this screen will be displayed.
	 * @return a new ExampleOutputPlugin screen.
	 */
	LCDSpicer2::Screen* createScreen(uint64_t seconds);

};

#endif /* EXAMPLE_PLUGINS_OUTPUT_EXAMPLEOUTPUTPLUGIN_HPP_ */
