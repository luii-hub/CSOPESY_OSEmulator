#include "Scheduler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <iomanip>
#include "ResourceManager.h"


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

bool Scheduler::initialize(ConfigurationManager* newConfigManager, ResourceManager *newResourceManager) {
    try {
        configManager = newConfigManager;
		  resourceManager = newResourceManager;
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

// TODO: implement RR scheduling
/*
void Scheduler::scheduleRR() {
    while (running) {
        std::lock_guard<std::mutex> lock(queueMutex);
        if (!readyQueue.empty()) {
            auto process = readyQueue.front();
            readyQueue.pop();

            auto coreID = getAvailableCoreWorkerID();

            if (coreID > 0) {
                process->setCore(coreID);
                cores[coreID - 1]->setProcess(process);

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
                quantums += 1;
                resourceManager->generateMemoryStampFile(quantums);
            }
            else {
                // No available core, put the process back at the front of the queue
                readyQueue.push(process);
            }
        }
    }
}
*/

void Scheduler::scheduleRR() {
    while (running) {
        std::lock_guard<std::mutex> lock(queueMutex);
        if (!readyQueue.empty()) {
            auto process = readyQueue.front();
            readyQueue.pop();

            auto coreID = getAvailableCoreWorkerID();

            if (coreID > 0) {
                process->setCore(coreID);
                cores[coreID - 1]->setProcess(process);

                // Start timing for quantum cycles
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(configManager->getQuantumCycles() * 1000)));

                // Callback to handle requeueing or marking as finished
                cores[coreID - 1]->setProcessCompletionCallback([this](const std::shared_ptr<Process>& completedProcess) {
                    std::lock_guard<std::mutex> queueLock(this->queueMutex);
                    if (!completedProcess->isFinished()) {
                        this->readyQueue.push(completedProcess);
                    }
                    else {
                        std::lock_guard<std::mutex> processLock(this->processMutex);
                        this->finishedProcesses.push_back(completedProcess);
                    }
                    });

                // Update quantum count and resource status
                quantums += 1;
                resourceManager->generateMemoryStampFile(quantums);
            }
            else {
                // No available core, put the process back at the front of the queue
                readyQueue.push(process);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Prevent busy-waiting
    }
}


const std::vector<std::unique_ptr<CoreWorker>>& Scheduler::getCoreWorkers() const {
    return cores;
}

const std::vector<std::shared_ptr<Process>>& Scheduler::getProcesses() const {
    return processes;
}
