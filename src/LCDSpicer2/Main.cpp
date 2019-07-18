/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Main.cpp
 * @ingroup		LCDSpicer2
 * @since		Oct 24, 2015
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

#include "Main.hpp"

#include "DataLoader.hpp"
#include "Refresh.hpp"

using namespace LCDSpicer2;

#define DEFAULT_INPUT_THREADS AUTO

Logger* Main::logger = nullptr;
bool Main::terminated = false;

Main::Main(const string& configFile) {

	string configurationFile;

	if (configFile.empty()) {
		configurationFile = PACKAGE_CONF_DIR "/" PACKAGE_NAME ".conf";
	}
	else {
		configurationFile = std::move(configFile);
	}

	// Get Configuration.
	configurationHandler = new Configuration(configurationFile);

	// Pass Configuration to the plugins.
	PluginHandler::setConfigurationHandler(*configurationHandler);

	configuration = configurationHandler->processNode("Main");
	// Setup logger.
	logger = Logger::getInstance(Logger::ALL); //ERROR | INFO | WARNING
	LOG(Logger::INFO, string("Program " PACKAGE_NAME " Initiated."));
}

Main::~Main() {

	for (auto pluginHandler : outputPluginHandlers) {
		delete pluginHandler;
	}

	for (auto pluginHandler : inputPluginHandlers) {
		delete pluginHandler;
	}

	LOG(Logger::INFO, "Program " PACKAGE_NAME " Terminated.");
	Logger::terminate();
	logger = nullptr;
}

inline void Main::initialize(bool daemonize, const string& dataFile) {

	if (daemonize) {
		if (daemonized) {
			throw Error("Already daemonized.");
		}

		LOG(Logger::DEBUG, "Daemonizing");
		if (daemon(0, 0) == -1) {
			throw Error("Unable to daemonize.");
		}
		LOG(Logger::DEBUG, "Daemonized");
	}

	// Load Data from data file.
	DataLoader dataLoader(dataFile);
	outputPluginHandlers = dataLoader.getOutputPluginHandlers();
	inputPluginHandlers  = dataLoader.getInputPluginHandlers();
	inputPluginWork      = dataLoader.getRefreshWork();

	int totalInputThreadsTemp = (configuration.find("InputThreads") != configuration.end()) ? configuration.at("InputThreads").getInt() : DEFAULT_INPUT_THREADS;
	if (totalInputThreadsTemp == AUTO) {
		uint total = 0;
		for (auto work : inputPluginWork) {
			total += work.second.size();
		}
		totalInputThreadsTemp = (total * inputPluginHandlers.size()) / 10;
		totalInputThreads = totalInputThreadsTemp ? totalInputThreadsTemp : 1;
	}

	for (auto inputPluginHandler : inputPluginHandlers) {
		inputPluginHandler->cleanFunctions();
	}

	delete configurationHandler;
}

int Main::detect() {

	auto configurationData = configurationHandler->getGroupSettings("Main");

	string tempDir = (configurationData.find("TempDir") != configurationData.end()) and !configurationData.at("TempDir").getString().empty() ? configurationData.at("TempDir").getString() : DEFAULT_TEMP_DIR;
	if (system(("mkdir -p " + tempDir).c_str()) == EXIT_FAILURE) {
		throw Error("Unable to create the temporary directory");
	}
	tempDir.append("/detected.js");

	FILE* pFile = fopen(tempDir.c_str(), "w");
	if (not pFile) {
		throw Error("Unable to open the js file (" + tempDir + ") to save contents.");
	}

	string oPath = PACKAGE_LIB_DIR OUTPUT_SUB_DIR;
	string tempStr = "var availableOutputs={";

	for (string plugin : PluginHandler::getPlugins(OUTPUT)) {
		OutputPluginHandler* outputPluginHandler;
		try {
			outputPluginHandler = new OutputPluginHandler(plugin, oPath);
			outputPluginHandler->initialize(true);
			tempStr += outputPluginHandler->showPluginCapabilities() + ",";
			outputPluginHandlers.push_back(outputPluginHandler);
		}
		catch (Error &e) {
			LOG(Logger::WARNING, "Unable to initialize output plugin " + plugin + " " + e.what());
			delete outputPluginHandler;
		}
	}
	if (not tempStr.empty() and tempStr[tempStr.size() - 1] == ',') {
		tempStr.resize(tempStr.size() - 1);
	}
	tempStr += "};\n";
	fputs(tempStr.c_str(), pFile);

	string iPath = PACKAGE_LIB_DIR INPUT_SUB_DIR;
	tempStr = "var availableInputs={";
	for (string plugin : PluginHandler::getPlugins(INPUT)) {
		InputPluginHandler* inputPluginHandler;

		try {
			inputPluginHandler = new InputPluginHandler(plugin, iPath);
			inputPluginHandler->initialize(true);
			tempStr += inputPluginHandler->showPluginCapabilities() + ",";
			inputPluginHandlers.push_back(inputPluginHandler);
		}
		catch (Error &e) {
			LOG(Logger::WARNING, "Unable to initialize input plugin " + plugin + " " + e.what());
			delete inputPluginHandler;
		}
	}
	if (not tempStr.empty() and tempStr[tempStr.size() - 1] == ',') {
		tempStr.resize(tempStr.size() - 1);
	}
	tempStr += "};\n";
	fputs(tempStr.c_str(), pFile);

	fclose(pFile);
	delete configurationHandler;
	return EXIT_SUCCESS;
}

void Main::signalHandler(int signal) {
	LOG(Logger::INFO, "Signal terminate received.");
	terminated = true;
}

inline int Main::run() {

	updatingWork.lock();
	// Create input refresh threads.
	thread* inputThreads = new thread[totalInputThreads];
	vector<int> inputThreadStatus(totalInputThreads, false);
	LOG(Logger::DEBUG, string("Creating ") + std::to_string(totalInputThreads) + " input thread/s");
	for (uint tnum = 0; tnum < totalInputThreads; tnum++) {
		inputThreads[tnum] = thread(&Main::inputRefreshThread, this, tnum, std::ref(inputThreadStatus.at(tnum)));
		inputThreads[tnum].detach();
	}

	// For every output Plugin create a thread.
	LOG(Logger::DEBUG, string("Creating ") + std::to_string(outputPluginHandlers.size()) + " output thread/s");
	thread* outputThreads = new thread[outputPluginHandlers.size()];
	vector<int> outputThreadStatus(outputPluginHandlers.size(), false);
	uint tnum = 0;

	for (auto outputPluginHandler : outputPluginHandlers) {
		outputPluginHandler->lock();
		// Set the buttons queue.
		outputPluginHandler->getLCD()->setButtonsPool(&buttonsPool);
		// Create thread.
		outputThreads[tnum] = thread(&Main::outputRefreshThread, this, tnum, std::ref(outputThreadStatus.at(tnum)), outputPluginHandler);
		outputThreads[tnum].detach();
		id_t newScreen = outputPluginHandler->selectScreen();
		workToDo[outputPluginHandler->getName()] = &inputPluginWork[outputPluginHandler->getName()][newScreen];
		outputPluginHandler->unLock();
		tnum++;
	}
	updatingWork.unlock();

	// Time LCDSpicer will wait when there is nothing to do.
	std::chrono::milliseconds ticks(TICK);

	// Main loop main thread taking care of:
	//	Screen rotation.
	//	TODO Input from hardware.
	//	TODO triggers.
	while (!terminated) {
		// Rotate screens
		for (auto handler : outputPluginHandlers) {
			if (handler->needsScreenRotation()) {
				// TODO: need to force a refresh in the needed information before we display the screen\
				to avoid empty data on the screens.
				updatingWork.lock();
				handler->lock();
				id_t newScreen = handler->selectScreen();
				workToDo[handler->getName()] = &inputPluginWork[handler->getName()][newScreen];
				updatingWork.unlock();
				handler->unLock();
			}
		}
		// Handle Buttons.
		while (not buttonsPool.empty()) {
			LOG(Logger::INFO, "Button pressed: " + std::to_string(buttonsPool.front()));
			buttonsPool.pop();
		}
		// Handle Triggers.
		std::this_thread::sleep_for(ticks);
	}

	// Wait for workers to finish before close.
	bool allGone = false;
	while (not allGone) {
		allGone = true;
		for (bool status : inputThreadStatus) {
			allGone &= !status;
		}

		for (bool status : outputThreadStatus) {
			allGone &= !status;
		}

		if (not allGone) {
			LOG(Logger::DEBUG, "Waiting for threads to finish");
			std::this_thread::sleep_for(ticks);
		}
	}

	delete[] inputThreads;
	delete[] outputThreads;
	return EXIT_SUCCESS;
}

void Main::inputRefreshThread(int threadNumber, int& status) {

	std::chrono::milliseconds ticks(TICK);

	LOG(Logger::DEBUG, "Input thread " + std::to_string(threadNumber + 1) + " initialized");

	// Report this worker active.
	status = true;
	vector<vector<Request>*> workCopy;

	// Thread main loop begins
	while (!terminated and status) {

		// Pick work.
		updatingWork.lock();
		workCopy.clear();
		for (auto workPerPlugin : workToDo) {
			workCopy.push_back(workPerPlugin.second);
		}

		updatingWork.unlock();

		for (auto workPerPlugin : workCopy) {
			for (auto work : *workPerPlugin)
				work.refresh();
		}

		std::this_thread::sleep_for(ticks);
	}

	// Clocking out the time card and going home.
	status = false;

	LOG(Logger::DEBUG, "Input thread " + std::to_string(threadNumber + 1) + " finished");
}

void Main::outputRefreshThread(int threadNumber, int& status, OutputPluginHandler* handler) {

	std::chrono::milliseconds ticks(TICK);

	OutputPlugin* plugin = handler->getLCD();

	LOG(Logger::DEBUG, "Output Plugin " + handler->getName() + " using thread " + std::to_string(threadNumber + 1) + " initialized");

	// Report this worker active.
	status = true;

	// Thread main loop begins.
	while (!terminated and status) {

		// Refresh plugins and process status.
		handler->lock();

		uint8_t result = plugin->refresh();
		if (result == STATUS_OK)
			plugin->getActiveScreen()->refresh();

		handler->unLock();

		// TODO do something with the results.
		switch (result) {
		case STATUS_UNSTABLE:
			LOG(Logger::DEBUG, "Output Plugin " + handler->getName() + " is unstable");
			break;
		case STATUS_OFFLINE:
			LOG(Logger::DEBUG, "Output Plugin " + handler->getName() + " is offline");
			break;
		case STATUS_AWAY:
			LOG(Logger::DEBUG, "Output Plugin " + handler->getName() + " is not doing anything");
			std::this_thread::sleep_for(ticks);
			break;
		}

		std::this_thread::sleep_for(ticks);
	}

	// Clocking out the time card and going home.
	status = false;

	LOG(Logger::DEBUG, "Output thread " + std::to_string(threadNumber + 1) + " finished");

}

/*
 * Main.
 *
 * Handles command line and runs the program.
 */
int main(int argc, char **argv) {

	// Process command line options.
	string commandline, dataFile, configFile = "";
	bool daemonize = true;
	bool detect = false;

	for (int i = 1; i < argc; i++) {

		commandline = argv[i];
		// Help text.
		if (commandline == "-h" or commandline == "--help") {
			cout << endl <<
				PACKAGE_NAME " command line usage:\n\n"
				"-c <conf> or --config <conf>\tUse an alternative configuration file\n"
				"-f or --foreground\t\tRun on foreground\n"
				"-d or --detect\t\t\tCreates a file to be used by the editor and stop.\n"
				"-v or --version\t\t\tDisplay version information\n"
				"-h or --help\t\t\tDisplay this help screen.\n"
				"Examples:\n"
				"\t" PACKAGE " file.lcdspicer -> Execute the program with default settings loading the file file.lcdspicer.\n"
				"\t" PACKAGE " -f file.lcdspicer -> Execute the program in foreground loading the file file.lcdspicer.\n"
				"\t" PACKAGE " -c /some/directory/config.conf file.lcdspicer -> Execute the program using a different configuration file and the file file.lcdspicer.\n"
				<< endl;
			return 0;
		}

		// Version Text.
		if (commandline == "-v" or commandline == "--version") {
			cout
				<< endl <<
				PACKAGE_STRING " Copyright © 2015 - 2016 - Patricio A. Rossi (MeduZa)\n\n"
				"For more information visit<" PACKAGE_URL ">\n\n"
				"To report errors or bugs visit <" PACKAGE_BUGREPORT ">\n"
				PACKAGE_NAME " is free software under the GPL 3 license\n\n"
				"See the GNU General Public License for more details <http://www.gnu.org/licenses/>."
				<< endl;
			return 0;
		}

		// Alternative configuration.
		if (commandline == "-c" or commandline == "--config") {
			configFile = argv[++i];
			continue;
		}

		// Force foreground.
		if (commandline == "-f" or commandline == "--foreground") {
			daemonize = false;
			continue;
		}

		// Detect features.
		if (commandline == "-d" or commandline == "--detect") {
			detect = true;
		}

		// Data filename.
		dataFile = argv[i];
	}

	if (not detect and dataFile.empty()) {
		cerr << endl << "You need to specify a file to load" << endl;
		return 0;
	}

	// Set the SIGTERM signal handler method.
	signal(SIGTERM, Main::signalHandler);

	Main program(configFile);

	try {
		if (detect) {
			return program.detect();
		}
		program.initialize(daemonize, dataFile);
	}
	catch (Error& e) {
		string theError = PACKAGE_NAME " terminated due to the error: ";
		theError.append(e.what());
		if (daemonize) {
			Logger* logger = Logger::getInstance();
			LOG(Logger::CRITICAL, theError);
		} else {
			cerr << endl << theError << endl;
		}
		return EXIT_FAILURE;
	}

	// Run LCDSpicer2.
	return program.run();
}
