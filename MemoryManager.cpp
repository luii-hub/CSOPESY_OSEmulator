#include <iostream>
#include "MemoryManager.h"

MemoryManager::MemoryManager() : running(false), backingStore("backing_store.txt") // Initialize running to false
{}

MemoryManager::~MemoryManager() {
    stop();
    if (memoryThread.joinable()) {
        memoryThread.join();
    }
}

bool MemoryManager::initialize(ConfigurationManager* configManager, Scheduler* scheduler) {
    try {
        this->configManager = configManager;
        this->scheduler = scheduler;
        allocationType = configManager->getMemoryManagerAlgorithm();

        // Initialize the memory allocator based on the configuration
        if (allocationType == "flat") {
            flatAllocator.initialize(configManager);
        }

        running = true;
        memoryThread = std::thread(&MemoryManager::run, this); // Start the memory manager thread
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing memory manager: " << e.what() << std::endl;
        return false;
    }
}

bool MemoryManager::allocate(Process process) {
    if (allocationType == "flat") {
        if (!flatAllocator.allocate(process)) {
            // If allocation fails, swap out a random process and try again
            std::unordered_set<int> runningProcessIDs = getRunningProcessIDs();
            int swappedOutProcessID = flatAllocator.swapOutRandomProcess(runningProcessIDs);

            if (swappedOutProcessID != -1) {
                auto swappedOutProcess = scheduler->getProcessByID(swappedOutProcessID);
                if (swappedOutProcess) {
                    backingStore.storeProcess(swappedOutProcess);
                }
            }

            return flatAllocator.allocate(process);
        }
        else {
            return true;
        }
    }
    return false;
}

void MemoryManager::deallocate(int pid) {
    if (allocationType == "flat") {
        flatAllocator.deallocate(pid);
    }
}

void MemoryManager::stop() {
    running = false;
}

void MemoryManager::run() {
    while (running) {
        // Perform periodic memory management tasks
        // For example: Check memory status, handle requests, etc.

        // Here, we'll just simulate work with sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Adjust as needed
    }
}

std::unordered_set<int> MemoryManager::getRunningProcessIDs() const {
    std::unordered_set<int> runningProcessIDs;
    for (const auto& core : scheduler->getCores()) {
        auto process = core->getCurrentProcess();
        if (process) {
            runningProcessIDs.insert(process->getID());
        }
    }
    return runningProcessIDs;
}

BackingStore* MemoryManager::getBackingStore() {
    return &backingStore;
}

int MemoryManager::getActiveMemory() {
    int totalActiveMemory = 0;
    for (const auto& core : scheduler->getCores()) {
        auto process = core->getCurrentProcess();
        if (process) {
            totalActiveMemory += process->getMemorySize();
        }
    }
    return totalActiveMemory;
}

int MemoryManager::getUsedMemory() {
    int totalActiveMemory = 0;
    if (configManager->getSchedulerAlgorithm() == "flat") {
        totalActiveMemory = flatAllocator.getUsedMemory();
    }
    return totalActiveMemory;
}

int MemoryManager::getInactiveMemory() {
    int totalInactiveMemory = 0;
    if (configManager->getSchedulerAlgorithm() == "flat") {
        totalInactiveMemory = flatAllocator.getInactiveMemory(getRunningProcessIDs());
    }
    return totalInactiveMemory;
}
