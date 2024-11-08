#include "Scheduler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <iomanip>
#include <ctime>


Scheduler::Scheduler() : running(false) {}

Scheduler::~Scheduler() {
    stop();
    if (schedulerThread.joinable()) {
        schedulerThread.join();
    }
    for (auto& core : cores) {
        core->stop();
    }
}

void Scheduler::addProcess(const std::shared_ptr<Process>& process) {
    std::lock_guard<std::mutex> lock(processMutex);
    processes.push_back(process);

    std::lock_guard<std::mutex> queueLock(queueMutex);
    readyQueue.push(process);
}


std::shared_ptr<Process> Scheduler::getProcessByName(const std::string& name) {
    std::lock_guard<std::mutex> lock(processMutex);
    for (auto& process : processes) {
        if (process->getName() == name) {
            return process;
        }
    }
    return nullptr;
}

std::shared_ptr<Process> Scheduler::getProcessByID(int pid) {
    std::lock_guard<std::mutex> lock(processMutex);
    for (auto& process : processes) {
        if (process->getID() == pid) {
            return process;
        }
    }
    return nullptr;
}

bool Scheduler::initialize(ConfigurationManager* newConfigManager) {
    try {
        configManager = newConfigManager;
        initializeCoreWorkers();
        running = true;
        run();
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing scheduler: " << e.what() << std::endl;
        return false;
    }
}

void Scheduler::logMemoryState(int quantumCycle) {
    // Create a filename with the quantum cycle number
    std::ostringstream filename;
    filename << "memory_stamp_" << std::setw(3) << std::setfill('0') << quantumCycle << ".txt";

    std::ofstream file(filename.str());
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename.str() << std::endl;
        return;
    }

    // Get current timestamp
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    struct tm buf;
    localtime_s(&buf, &in_time_t);

    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%m/%d/%Y %I:%M:%S%p", &buf);

    // Simulate fragmentation (as a constant example value)
    int fragmentation = 8192;  // Example external fragmentation amount in KB

    // Write header information to file
    file << "Timestamp: (" << timestamp << ")\n";
    file << "Number of processes in memory: " << processes.size() << "\n";
    file << "Total external fragmentation in KB: " << fragmentation << "\n\n";

    // ASCII memory layout
    int totalMemory = 16384;  // Example total memory size in KB
    file << "----end----- = " << totalMemory << "\n";

    // Print each process's start and end addresses
    for (const auto& process : processes) {
        file << std::setw(5) << process->getStartAddress() << "     " << process->getName() << "\n";
    }

    // Free memory representation
    file << "----start----- = 0\n";

    file.close();
}

// Function to assign simulated memory addresses
void Scheduler::assignMemoryAddresses() {
    int startAddress = 16384;  // Starting from a hypothetical total memory size
    for (auto& process : processes) {
        int processMemory = 4096;  // Example fixed memory size per process
        int endAddress = startAddress;
        startAddress -= processMemory;
        process->setMemoryAddresses(startAddress, endAddress);
    }
}

void Scheduler::initializeCoreWorkers() {
    for (int i = 0; i < configManager->getNumCPU(); i++) {
        if (configManager->getSchedulerAlgorithm() == "rr") {
            cores.emplace_back(std::make_unique<CoreWorker>(i + 1, configManager->getDelayPerExec(), configManager->getQuantumCycles()));
            cores.back()->start();
        }

        else {
            cores.emplace_back(std::make_unique<CoreWorker>(i + 1, configManager->getDelayPerExec()));
            cores.back()->start();
        }

    }
}

void Scheduler::run() {
    schedulerThread = std::thread(&Scheduler::schedulerLoop, this);
}

void Scheduler::schedulerLoop() {
    while (running) {
        if (configManager->getSchedulerAlgorithm() == "fcfs") {
            scheduleFCFS();
        }
		else if (configManager->getSchedulerAlgorithm() == "rr") {
			scheduleRR();
		}

        std::this_thread::sleep_for(std::chrono::duration<float>(configManager->getDelayPerExec()));
    }
}

void Scheduler::stop() {
    running = false;
}

const std::vector<std::unique_ptr<CoreWorker>>& Scheduler::getCores() const {
    return cores;
}

int Scheduler::getAvailableCoreWorkerID() {
    for (auto& core : cores) {
        if (core->isAvailable()) {
            return core->getID();
        }
    }
    return 0;
}

void Scheduler::scheduleFCFS() {
    while (running) {
        std::lock_guard<std::mutex> lock(queueMutex);
        if (!readyQueue.empty()) {

            auto process = readyQueue.front();
            readyQueue.pop();

            auto coreID = getAvailableCoreWorkerID();

            if (coreID > 0) {
                process->setCore(coreID);
                cores[coreID - 1]->setProcess(process);
            }

            else {
                // No available core, put the process back at the front of the queue
                std::queue<std::shared_ptr<Process>> tempQueue;
                tempQueue.push(process);
                while (!readyQueue.empty()) {
                    tempQueue.push(readyQueue.front());
                    readyQueue.pop();
                }
                readyQueue = tempQueue;
            }
        }
    }
}

// Integrate logMemoryState into scheduleRR (Round-Robin scheduling)
void Scheduler::scheduleRR() {
    int quantumCycle = 0;
    assignMemoryAddresses();  // Call this once to set memory addresses initially

    while (running) {
        std::lock_guard<std::mutex> lock(queueMutex);
        if (!readyQueue.empty()) {
            auto process = readyQueue.front();
            readyQueue.pop();

            auto coreID = getAvailableCoreWorkerID();

            if (coreID > 0) {
                process->setCore(coreID);
                cores[coreID - 1]->setProcess(process);

                // Log memory state every quantum cycle
                logMemoryState(quantumCycle);
                quantumCycle++;

                // Use a lambda function to handle requeueing the process after execution
                cores[coreID - 1]->setProcessCompletionCallback([this](const std::shared_ptr<Process>& completedProcess) {
                    if (!completedProcess->isFinished()) {
                        std::lock_guard<std::mutex> queueLock(this->queueMutex);
                        this->readyQueue.push(completedProcess);
                    }
                    else {
                        std::lock_guard<std::mutex> processLock(this->processMutex);
                        this->finishedProcesses.push_back(completedProcess);
                    }
                });
            }
            else {
                // No available core, put the process back at the front of the queue
                readyQueue.push(process);
            }
        }

        std::this_thread::sleep_for(std::chrono::duration<float>(configManager->getQuantumTime()));
    }
}
const std::vector<std::unique_ptr<CoreWorker>>& Scheduler::getCoreWorkers() const {
    return cores;
}

const std::vector<std::shared_ptr<Process>>& Scheduler::getProcesses() const {
    return processes;
}
