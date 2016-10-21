/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Main.hpp
 * @defgroup	LCDSpicer2 LCDSpicer 2
 * @defgroup	general General Utilities
 * @defgroup	plugins Plugins
 * @since		Oct 24, 2015
 *
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
 *
 * @mainpage	LCDSpicer 2 screen content editor
 * <p>LCDSpicer 2 is a screen contents editor that can be used to display information on Liquid Crystal Displays (LCDs) or any supported display screen.<br>
 * The program allows the creation of screens that can display system states, information, hard drives, partitions, sensors, music players, CPU / network stats, and computer health overall, the input is feeded using plugins, this plugins allows you to add new features. It also support many outputs at the same time using plugins.</p>
 *
 */

#ifndef SRC_LCDSPICER2_MAIN_HPP_
#define SRC_LCDSPICER2_MAIN_HPP_ 1

// IO stream.
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// To handle daemonization.
#include <unistd.h>

// to handle threads.
#include <thread>
#include <future>
using std::thread;

// To handle c signals.
#include <csignal>
using std::signal;

// Compilation settings.
#include "config.h"

#include <vector>
using std::vector;

// Logger.
#include "Logger.hpp"

// To handle requests.
#include "Request.hpp"

// The LCDSpicer 2 namespace.
namespace LCDSpicer2 {

/**
 * Main Class, is called on program creation and handles everything.
 */
class Main {

public:

	/**
	 * Creates a Main object.
	 *
	 * @param configFile alternative configuration file (other than system one).
	 */
	Main(const string& configFile);

	/**
	 * Finalize the Main object.
	 */
	virtual ~Main();

	/**
	 * Initialize the program.
	 *
	 * @param daemonize true if the program needs to run as a daemon.
	 * @param dataFile the file to load.
	 */
	void initialize(bool daemonize, const string& dataFile);

	/**
	 * Main execution method.
	 * @return the exit code.
	 */
	int run();

	/**
	 * Run the detection routine.
	 *
	 * @return the exit code.
	 */
	int detect();

	/**
	 * Handles the SIGTERM signal.
	 *
	 * @param signal
	 */
	static void signalHandler(int signal);

private:

	/// Keeps an instance of the configuration loader.
	Configuration* configurationHandler;

	/// The logger instance.
	static Logger* logger;

	/// Flag to mark the daemonized state.
	bool daemonized = false;

	/// The number of input threads.
	uint totalInputThreads = 0;

	/// flag used to handle program termination.
	static bool terminated;

	/// A vector to with the pointers the output plugin handlers.
	vector<OutputPluginHandler*> outputPluginHandlers;

	/// A vector with the pointers to the input plugin handlers.
	vector<InputPluginHandler*> inputPluginHandlers;

	/// A map by output plugin name, screen id to the refresh work.
	umap<string, umap<id_t,vector<Request>>> inputPluginWork;

	/// Current Work to do.
	umap<string, vector<Request>*> workToDo;

	/// Keeps track of the data updating to avoid plugins to pick work when is changing.
	mutex updatingWork;

	/// The queue where the key strokes are stored.
	queue<uint8_t> buttonsPool;

	/// Stores the program configuration.
	umap<string, Value> configuration;

	/**
	 * Function used by the input threads.
	 *
	 * @param threadNumber the thread index.
	 * @param status is set to true when the worker is running and false when it finish,
	 * also can be externally set to false for force that thread to finish.
	 */
	void inputRefreshThread(int threadNumber, int& status);

	/**
	 * Function used by the input threads.
	 *
	 * @param threadNumber Informative only.
	 * @param status Is set to true when the worker is running and false when it finish,
	 * also can be externally set to false for force that thread to finish.
	 * @param handler The output plugin to work on.
	 */
	void outputRefreshThread(int threadNumber, int& status, OutputPluginHandler* handler);

};

/**
 * Main function.
 *
 * @param argc
 * @param argv
 * @return exit code.
 */
int main(int argc, char **argv);

};

#endif /* SRC_LCDSPICER2_MAIN_HPP_ */
