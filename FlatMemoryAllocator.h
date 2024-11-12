#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Process.h"
#include "ConfigurationManager.h"
#include "MemoryBlock.h"


class FlatMemoryAllocator
{
public:
	FlatMemoryAllocator();

	void initialize(ConfigurationManager* configManager); // initialize memory blocks
	bool allocate(Process process);	// allocate memory for a process
	void deallocate(int pid);
	int swapOutRandomProcess(const std::unordered_set<int>& runningProcessIDs); // swap out a random process
	void displayMemory();

	int getUsedMemory(); // returns active + idle processes 
	int getInactiveMemory(const std::unordered_set<int>& runningProcessIDs);
	std::vector<MemoryBlock> getProccessMemoryBlocks() const;
	
private:
	ConfigurationManager* configManager;
	std::vector<MemoryBlock> memoryBlocks; // memory blocks
	std::unordered_map<int, int> processMemoryMap; // memory block index
	int memorySize;	// total memory size

	void mergeFreeBlocks(); // merge adjacent free blocks
};

