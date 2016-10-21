/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file		Kernel.cpp
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

#include "Kernel.hpp"

// To handle files.
#include <cstdio>

// For kernel name.
#include <sys/utsname.h>

#include "Hertz.hpp"
#include "DigitalInformation.hpp"

// Plugin factory functions.
#ifdef inputPluginFactory
	inputPluginFactory(Kernel)
#else
	#error "Plugin factory function missing."
#endif

// Removing the annoying unused-result warning.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

bool Kernel::initialize() {
	// Read CPU info
	return (readCpuData() ? STATUS_OK : STATUS_UNSTABLE);
}

Value Kernel::processRequest(const RequestData& requestData) {

	Value temp;

	switch (requestData.function) {

	case CPU_INFORMATION:

		switch (requestData.subFunction) {

		case CPU_NAME:
			if (cpuInformation.empty())
				readCpuName();
			temp.set(cpuInformation);
			break;

		case CPU_MAX_SPEED:
			readCpuFreq(requestData.symbol);
			temp.set(cpuFreq);
			break;

		case CPU_SPEED:
			uint cpuN = 0;
			try {
				cpuN = std::stoul(requestData.data);
			}
			catch (...) {}

			readCpuCurFreq(requestData.data, cpuN);
			temp.set(cpuCurFreq[cpuN]);
			break;
		}
	break;

	case CPU_LOAD: {

		if (requestData.needUpdate())
			readCpuLoad();

		uint cpuN = 0;
		try {
			cpuN = std::stoul(requestData.data);
		}
		catch (...) {}

		switch(requestData.subFunction) {

		case CPU_TOTAL:
			temp.set(percents[cpuN].total);
			break;

		case CPU_USER:
			temp.set(percents[cpuN].user);
			break;

		case CPU_NICE:
			temp.set(percents[cpuN].nice);
			break;

		case CPU_SYS:
			temp.set(percents[cpuN].sys);
			break;

		case CPU_IDLE:
			temp.set(percents[cpuN].idle);
			break;
		}
	}
	break;

	case SYSTEM_INFORMATION:

		switch(requestData.subFunction) {

		case KERNEL:
			if (kernel.empty())
				readKernel();
			temp.set(kernel);
			break;

		case HOSTNAME:
			if (hostname.empty())
				readHostname();
			temp.set(hostname);
			break;

		case DOMAINNAME:
			if (domainname.empty())
				readDomainName();
			temp.set(domainname);
			break;

		case UPTIME:
			readUpTime();
			temp.set(uptime);
			break;

		case DISTRIBUTION:
			if (distribution.empty())
				readDistribution();
			temp.set(distribution);
			break;
		}
	break;

	case MEMORY_INFORMATION: {

		uint64_t val;

		if (requestData.needUpdate())
			readMemory();

		switch(requestData.subFunction) {

		case MEMORY_TOTAL:
			val = memory[MEM_TOTAL];
			break;

		case MEMORY_FREE:
			val = memory[MEM_AVAIL];
			break;

		case MEMORY_USED:
			val = memory[MEM_TOTAL] - memory[MEM_AVAIL];
			break;

		case MEMORY_FREE_P:
			if (memory[MEM_TOTAL])
				temp.set(memory[MEM_AVAIL] * 100 / memory[MEM_TOTAL]);
			return temp;

		case MEMORY_USED_P:
			if (memory[MEM_TOTAL])
				temp.set((memory[MEM_TOTAL] - memory[MEM_AVAIL]) * 100 / memory[MEM_TOTAL]);
			return temp;

		case SWAP_TOTAL:
			val = memory[SWA_TOTAL];
			break;

		case SWAP_FREE:
			val = memory[SWA_AVAIL];
			break;

		case SWAP_USED:
			val = memory[SWA_TOTAL] - memory[SWA_AVAIL];
			break;

		case SWAP_FREE_P:
			if (memory[SWA_TOTAL])
				temp.set(memory[SWA_AVAIL] * 100 / memory[SWA_TOTAL]);
			return temp;

		case SWAP_USED_P:
			if (memory[SWA_TOTAL])
				temp.set((memory[SWA_TOTAL] - memory[SWA_AVAIL]) * 100 / memory[SWA_TOTAL]);
			return temp;
		}

		if (not requestData.symbol) {
			temp.set(val);
		}
		else {
			DigitalInformation converter(UNIT_KIBIBYTE);
			temp.set(converter.getString(val, requestData.symbol));
		}

		break;
	}
	}
	return temp;
}

void Kernel::readKernel() {

	// Two ways to extract the kernel information:
	// 1 using utsname:
	utsname u_name;
	uname(&u_name);
	kernel
		.append(u_name.sysname)
		.append(" ")
		.append(u_name.release)
		.append(" ")
		.append(u_name.version)
		.append(" ")
		.append(u_name.machine);

	// 2 using proc:
	/*kernel =
		readLine("/proc/sys/kernel/ostype") +
		" " +
		readLine("/proc/sys/kernel/osrelease") +
		" " +
		readLine("/proc/sys/kernel/version");*/
}

void Kernel::readHostname() {
	hostname = readLine("/proc/sys/kernel/hostname");
}

void Kernel::readDomainName() {
	domainname = readLine("/proc/sys/kernel/domainname");
}

void Kernel::readUpTime() {

	FILE* pFile = std::fopen("/proc/uptime", "r");
	if (not pFile)
		return;

	uint day, hou, min, sec;
	bool goes = false;

	std::fscanf(pFile, "%u", &sec);

	std::fclose(pFile);

	uptime.clear();

	// Days.
	day = sec / 86400;
	if (day) {
		uptime.append(std::to_string(day) + " Day");
		goes = true;
		if (day != 1)
			uptime.append("s");
	}
	if (goes)
		uptime.append(" ");
	sec = sec % 86400;

	// Hours.
	hou = sec / 3600;
	if (goes or hou) {
		goes = true;
		uptime.append(std::to_string(hou) + " Hour");
		if (hou != 1)
			uptime.append("s");
	}
	if (goes)
		uptime.append(" ");
	sec = sec % 3600;

	// Minutes.
	min = sec / 60;
	if (goes or min) {
		uptime.append(std::to_string(min) + " Min");
		goes = true;
		if (min != 1)
			uptime.append("s");
	}
	if (goes)
		uptime.append(" ");

	// Seconds.
	sec = sec % 60;
	uptime.append(std::to_string(sec) + " Sec");
	if (sec != 1)
		uptime.append("s");
}

void Kernel::readDistribution() {

	FILE* pFile = std::fopen("/etc/os-release", "r");
		if (not pFile)
			return;

	char buffer[256];

	std::fscanf(pFile, "NAME=\"%[^\"]\"", buffer);
	distribution = buffer;
	buffer[0] = '\0';

	std::fscanf(pFile, " VERSION=\"%[^\"]\"", buffer);
	distribution.append(" ").append(buffer);
	std::fclose(pFile);
}

void Kernel::readMemory() {

	FILE* pFile = std::fopen("/proc/meminfo", "r");
		if (not pFile)
			return;

		uint64_t val;
		char str[256];
		int n;
		string elements[4] = {
			"MemTotal:",
			"MemAvailable:",
			"SwapTotal:",
			"SwapFree:"
		};

		for (uint c = 0; c < 4; c++) {
			do {
				n = std::fscanf(pFile, "%s %lu %*s", str, &val);

				if (elements[c] == str) {
					memory[c] = val;
					break;
				}
			}
			while (n != EOF);
			if (n == EOF)
				break;
		}

		std::fclose(pFile);
}

bool Kernel::readCpuData() {

	// Read the number of CPUs;
	int n;

	FILE* pFile = std::fopen(CPU_NUMBER_LOCATION, "r");
	if (not pFile)
		return false;

	if (not std::fscanf(pFile, "%*i-%u", &cpus)) {
		std::fclose(pFile);
		return false;
	}

	std::fclose(pFile);

	cpus++;

	percents.resize(cpus + 1);
	previousRead.resize(cpus + 1);
	cpuCurFreq.resize(cpus +1 );

	return true;
}

void Kernel::readCpuName() {

	FILE* pFile = std::fopen(CPU_DATA_LOCATION, "r");
	if (not pFile)
		return;

	int n;
	char buffer[256];

	do {
		n = std::fscanf(pFile, " model name : %256[^\n] ", buffer);
		if (n > 0) {
			break;
		}
		n = std::fscanf(pFile,"%*s");
	}
	while (EOF != n);
	std::fclose(pFile);

	cpuInformation = std::move(buffer);
}

void Kernel::readCpuFreq(int16_t symbol) {

	uint64_t cpuFreq = 0;
	// Read CPU MAX FREQ
	FILE* pFile = std::fopen(CPU_FREQ_LOCATION, "r");
	if (not pFile)
		return;

	std::fscanf(pFile, "%lu", &cpuFreq);

	std::fclose(pFile);

	if (not symbol) {
		this->cpuFreq = std::to_string(cpuFreq);
	}
	else {
		// Convert hertz into desired format.
		Hertz converter(UNIT_KILOHERTZ);
		this->cpuFreq = converter.getString(cpuFreq, symbol);
	}
}

void Kernel::readCpuCurFreq(const string& cpu, uint cpuN) {

	if (cpuN < 1)
		return;

	string file = CPU_CUR_FREQ_LOCATION;
	file.replace(27, 0, cpu);

	FILE* pFile = std::fopen(file.c_str(), "r");
	if (not pFile)
		return;

	std::fscanf(pFile, "%lu", &cpuCurFreq[cpuN]);

	std::fclose(pFile);
}

bool Kernel::readCpuLoad() {

	uint64_t cpuN = 0, iowait = 0, irq = 0, softirq = 0;
	string buffer;
	char c;
	cpuElements reads;

	FILE* pFile = std::fopen (CPU_STAT_LOCATION, "r");
	if (not pFile)
		return false;

	while (true) {
		do {

			c = std::fgetc(pFile);
			if (c == EOF)
				break;

			buffer.push_back(c);

		} while (c != '\n');

		if (buffer.empty() || buffer[0] == 'i')
			break;

		std::sscanf(
			&buffer[0],
			"%*s %lu %lu %lu %lu %lu %lu %lu",
			&reads.user,
			&reads.nice,
			&reads.sys,
			&reads.idle,
			&iowait,
			&irq,
			&softirq
		);

		reads.sys += iowait + irq + softirq;
		reads.total = reads.user + reads.nice + reads.sys + reads.idle;
		uint64_t diff = reads.total - previousRead[cpuN].total;

		if (diff) {
			percents[cpuN].total	= ((reads.user + reads.nice + reads.sys) - (previousRead[cpuN].user + previousRead[cpuN].nice + previousRead[cpuN].sys)) * 100 / diff;
			percents[cpuN].user		= (reads.user	- previousRead[cpuN].user)	* 100 / diff;
			percents[cpuN].nice		= (reads.nice	- previousRead[cpuN].nice)	* 100 / diff;
			percents[cpuN].sys		= (reads.sys	- previousRead[cpuN].sys)	* 100 / diff;
			percents[cpuN].idle		= (reads.idle	- previousRead[cpuN].idle)	* 100 / diff;
		}
		previousRead[cpuN].total	= reads.total;
		previousRead[cpuN].user		= reads.user;
		previousRead[cpuN].nice		= reads.nice;
		previousRead[cpuN].sys		= reads.sys;
		previousRead[cpuN].idle		= reads.idle;

		if (c == EOF)
			break;

		buffer.clear();
		cpuN++;
	}
	std::fclose(pFile);
	return true;
}

string Kernel::readLine(const char* file) {

	FILE* pFile = std::fopen(file, "r");
	if (not pFile)
		return "";

	char buffer[256];

	std::fscanf(pFile, "%256s", buffer);

	std::fclose(pFile);

	return buffer;
}

void Kernel::detectFunctionsValues(callBack_t callBack) {

	umap<string, string> temp1;

	temp1.insert({"Total", "0"});
	for (uint c = 1; c <= cpus; c++)
		temp1.insert({"CPU " + std::to_string(c), std::to_string(c)});

	for (int e = 0; e < CPU_ELEMENTS; e++)
		callBack(CPU_LOAD, e + 1, temp1);

	temp1.clear();
	// Per CPU/s / core/s
	for (uint c = 1; c <= cpus; c++)
		temp1.insert({"CPU " + std::to_string(c), std::to_string(c)});

	callBack(CPU_INFORMATION, CPU_SPEED, std::move(temp1));

};

#pragma GCC diagnostic pop
