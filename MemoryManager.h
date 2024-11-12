#pragma once

#include <thread>
#include <atomic>
#include <iostream>
#include <vector>

#include "Scheduler.h"
#include "ConfigurationManager.h"
#include "Process.h"
#include "FlatMemoryAllocator.h"
#include "PagingAllocator.h"
#include "BackingStore.h"

class MemoryManager
{
public:
	MemoryManager();
	~MemoryManager();
	FlatMemoryAllocator flatAllocator;
	PagingAllocator pagingAllocator;

	bool initialize(ConfigurationManager* configManager, Scheduler* scheduler);
	bool allocate(Process process);
	void deallocate(int pid);

	void stop(); // Method to stop the thread
	BackingStore* getBackingStore();

	// Get total active memory
	int getActiveMemory();
	int getUsedMemory();
	int getInactiveMemory();

	// Get Memory used by a specific process
	std::vector<MemoryBlock> getProccessMemoryBlocks() const;

private:
	void run(); // Method that the thread will execute

	ConfigurationManager* configManager;
	Scheduler* scheduler;
	BackingStore backingStore;

	std::string allocationType;

	std::thread memoryThread;
	std::atomic<bool> running;

	std::unordered_set<int> getRunningProcessIDs() const; // get running process IDs

};
