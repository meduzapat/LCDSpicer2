
#include "ExampleOutputPlugin.hpp"

// This blocks need to be added to any output plugin.
#ifdef outputPluginFactory
	outputPluginFactory(ExampleOutputPlugin)
#else
	#error "Plugin factory function missing."
#endif

ExampleOutputPlugin::~ExampleOutputPlugin() {
	LOG(DEBUG, "ExampleOutputPlugin Destroyed");
}

bool LCDProc::initialize() {
	LOG(DEBUG, "ExampleOutputPlugin Created");
	return STATUS_OK;
}

uint8_t LCDProc::refresh() {
	activeScreen->refresh();
	return STATUS_OK;
}

LCDSpicer2::Screen* ExampleOutputPlugin::createScreen(uint64_t seconds) {
	return new ExampleOutputPlugin(seconds);
}
