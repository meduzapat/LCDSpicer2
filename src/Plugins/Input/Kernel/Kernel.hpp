/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Kernel.hpp
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

#ifndef SRC_PLUGINS_INPUT_KERNEL_HPP_
#define SRC_PLUGINS_INPUT_KERNEL_HPP_

#include "InputPlugin.hpp"

using namespace LCDSpicer2;

#define CPU_DATA_LOCATION		"/proc/cpuinfo"
#define CPU_STAT_LOCATION		"/proc/stat"
#define CPU_NUMBER_LOCATION		"/sys/devices/system/cpu/present"
// NOTE: I Assuming that all CPUs have the same max frequency per system, no sure if this is right.
#define CPU_FREQ_LOCATION		"/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq"
#define CPU_CUR_FREQ_LOCATION	"/sys/devices/system/cpu/cpu/cpufreq/cpuinfo_cur_freq"

#define CPU_INFORMATION		1
#define CPU_NAME		1
#define CPU_MAX_SPEED	2
#define CPU_SPEED		3

#define CPU_LOAD			2
#define CPU_TOTAL		1
#define CPU_USER		2
#define CPU_NICE		3
#define CPU_SYS			4
#define CPU_IDLE		5

#define SYSTEM_INFORMATION	3
#define KERNEL			1
#define HOSTNAME		2
#define DOMAINNAME		3
#define UPTIME			4
#define DISTRIBUTION	5

#define MEMORY_INFORMATION	4
#define MEMORY_TOTAL	1
#define MEMORY_FREE		2
#define MEMORY_USED		3
#define MEMORY_FREE_P	4
#define MEMORY_USED_P	5
#define SWAP_TOTAL		6
#define SWAP_FREE		7
#define SWAP_USED		8
#define SWAP_FREE_P		9
#define SWAP_USED_P		10

#define MEM_TOTAL 0
#define MEM_AVAIL 1
#define SWA_TOTAL 2
#define SWA_AVAIL 3

#define CPU_ELEMENTS 5

struct cpuElements {
	uint64_t total	= 0;
	uint64_t user	= 0;
	uint64_t nice	= 0;
	uint64_t sys	= 0;
	uint64_t idle	= 0;
};

/**
 * LCDSpicer2::Users
 */
class Kernel: public InputPlugin {

public:

	bool initialize();

	void detectFunctionsValues(callBack_t callBack);

protected:

	Value processRequest(const RequestData& requestData);

private:

	/// Keeps the previous load reads.
	vector<cpuElements> previousRead;

	/// Keeps previous values.
	vector<cpuElements> percents;

	/// Keeps the number of detected CPUs/cores.
	uint cpus = 0;

	/// Keeps the information about the CPU/s.
	string cpuInformation;

	/// Stores the maximum CPU frequency speed.
	string cpuFreq;

	/// Stores the CPUs current frequency speed.
	vector<uint64_t> cpuCurFreq;

	/// Stores the kernel data.
	string kernel;

	/// Keeps the hostname.
	string hostname;

	/// keeps the domainname.
	string domainname;

	/// Stores the processed uptime.
	string uptime;

	/// Keeps the OS release.
	string distribution;

	/// Memory elements: MemTotal, MemAvailable, SwapTotal, SwapFree.
	uint64_t memory[4] = {0, 0, 0, 0};

	/**
	 * Reads the CPU name and model.
	 */
	void readCpuName();

	/**
	 * Reads information from the CPU that never changes.
	 *
	 * @return true on success, false instead.
	 */
	bool readCpuData();

	/**
	 * Reads the CPU frequency.
	 *
	 * @param symbol the desired unit format, -1 means no symbol.
	 */
	void readCpuFreq(int16_t symbol);

	/**
	 * Extracts the current CPU frequency.
	 *
	 * @param cpu the CPU number stating from 1.
	 */
	void readCpuCurFreq(const string& cpu, uint cpuN);

	/**
	 * Extracts the CPU load information for every CPU.
	 *
	 * @return true on success, false instead.
	 */
	bool readCpuLoad();

	/**
	 * Extracts the kernel information.
	 */
	void readKernel();

	/**
	 * Reads the hostname.
	 */
	void readHostname();

	/**
	 * Reads the domain name.
	 */
	void readDomainName();

	/**
	 * Reads the uptime.
	 */
	void readUpTime();

	/**
	 * Extracts the distribution information.
	 */
	void readDistribution();

	/**
	 * Extracts the memory information.
	 */
	void readMemory();

	/**
	 * Helper function to read files.
	 *
	 * @param file full path to the file.
	 * @return the read data.
	 */
	string readLine(const char* file);
};

#endif /* SRC_PLUGINS_INPUT_KERNEL_HPP_ */
