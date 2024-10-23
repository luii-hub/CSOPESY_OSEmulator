#include "Scheduler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <iomanip>


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

void Scheduler::addProcess(const Process& process) {
    std::lock_guard<std::mutex> lock(processMutex);
    auto newProcess = std::make_shared<Process>(process);
    processes.push_back(newProcess);

    std::lock_guard<std::mutex> queueLock(queueMutex);
    readyQueue.push(newProcess);
}


std::shared_ptr<Process> Scheduler::getProcessByName(const std::string name) {
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

void Scheduler::initializeCoreWorkers() {
    for (int i = 0; i < configManager->getNumCPU(); i++) {
        if (configManager->getSchedulerAlgorithm() == "rr") {
            cores.emplace_back(std::make_unique<CoreWorker>(
                i + 1, 
                configManager->getDelayPerExec(), 
                configManager->getQuantumCycles()
            ));
            
            // Set up callback for RR scheduling
            cores.back()->setProcessCompletionCallback(
                [this](std::shared_ptr<Process> process) {
                    std::lock_guard<std::mutex> lock(queueMutex);
                    if (!process->isFinished()) {
                        readyQueue.push(process);
                    }
                }
            );
        }
        else {
            cores.emplace_back(std::make_unique<CoreWorker>(
                i + 1, 
                configManager->getDelayPerExec()
            ));
        }
        cores.back()->start();
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

void Scheduler::scheduleRR() {
    while (running) {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            
            // Check all cores for processes that need preemption
            for (auto& core : cores) {
                if (!core->isAvailable()) {
                    auto currentProcess = core->getCurrentProcess();
                    if (currentProcess && !currentProcess->isFinished() && 
                        currentProcess->getCyclesInCore() >= configManager->getQuantumCycles()) {
                        // Preempt the process
                        currentProcess->resetCyclesInCore();
                        readyQueue.push(currentProcess);
                        core->preemptProcess();
                    }
                }
            }

            // Assign processes to available cores
            if (!readyQueue.empty()) {
                auto process = readyQueue.front();
                readyQueue.pop();

                auto coreID = getAvailableCoreWorkerID();
                if (coreID > 0) {
                    process->setCore(coreID);
                    process->resetCyclesInCore();
                    cores[coreID - 1]->resetQuantumTimer();
                    cores[coreID - 1]->setProcess(process);
                }
                else {
                    // No available core, put process back in queue
                    readyQueue.push(process);
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::duration<float>(configManager->getDelayPerExec()));
    }
}

const std::vector<std::unique_ptr<CoreWorker>>& Scheduler::getCoreWorkers() const {
    return cores;
}

const std::vector<std::shared_ptr<Process>>& Scheduler::getProcesses() const {
    return processes;
}