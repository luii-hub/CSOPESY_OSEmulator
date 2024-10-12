#include "Process.h"
#include <iostream>

#include "ConsoleManager.h"

extern ConsoleManager consoleManager;	

Process::Process() : id(0), totalInstructions(0), memorySize(0), pageSize(0) {
	// Initialize other members if needed
}

Process::Process(std::string name, int id, int totalInstructions, float memorySize, float pageSize)
	:	processName(name), 
		id(id), 
		currentInstruction(0), 
		totalInstructions(totalInstructions), 
		core(-1), 
		finished(false), 
		creationTime(std::chrono::system_clock::now()),
		memorySize(memorySize),
		pageSize(pageSize)

{}

std::string Process::getName() const {
	return processName;
}

int Process::getID() const {
	return id;
}

int Process::getCurrentInstruction() const {
	return currentInstruction;
}

int Process::getTotalInstructions() const {
	return totalInstructions;
}

int Process::getRemainingInstructions() const {
	return totalInstructions - currentInstruction;
}

int Process::getCore() {
	return core;
}

void Process::setCore(int coreID) {
	core = coreID;
};

bool Process::isFinished() const {
	return finished;
}

std::string Process::getCreationTime() const {
	auto creationTimeT = std::chrono::system_clock::to_time_t(creationTime);
	struct tm timeinfo;
	localtime_s(&timeinfo, &creationTimeT);
	char buffer[100];
	std::strftime(buffer, sizeof(buffer), "%m/%d/%Y %I:%M:%S%p", &timeinfo);
	return buffer;
}

float Process::getMemorySize() const {
	return memorySize;
}

float Process::getPageSize() const {
	return pageSize;
}

void Process::execute() {
	if (currentInstruction < totalInstructions) { // If the process has not finished executing
		currentInstruction++; // Increment the current instruction
	} else {
		finished = true; // Set the process to finished
	}
}