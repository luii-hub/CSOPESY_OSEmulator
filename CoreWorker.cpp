#include "CoreWorker.h"

#include <iostream>

CoreWorker::CoreWorker(int id, float delayPerExec, float quantumSlice) 
    : id(id), delayPerExec(delayPerExec), quantumSlice(quantumSlice), running(false), processAssigned(false) {}

CoreWorker::~CoreWorker() {
    stop();
    if (coreThread.joinable()) {
        coreThread.join();
    }
}

std::shared_ptr<Process> CoreWorker::getCurrentProcess() {
	std::lock_guard<std::mutex> lock(coreMutex);
	return currentProcess;
}

void CoreWorker::setProcess(std::shared_ptr<Process> process) {
    std::lock_guard<std::mutex> lock(coreMutex);
    currentProcess = process;
    processAssigned = true;
}

void CoreWorker::runProcess() {
    if (!currentProcess) return;

    // For FCFS
    if (quantumSlice == 0) {
        while (currentProcess && !currentProcess->isFinished()) {
            totalActiveTicks++;
            currentProcess->execute();
            std::this_thread::sleep_for(std::chrono::duration<float>(delayPerExec));
        }

        if (currentProcess && currentProcess->isFinished()) {
            finishProcess();
        }
    }
    // For RR
    else {
        if (currentProcess->isFinished()) {
            finishProcess();
            return;
        }

        currentProcess->execute();
        currentQuantumTime++;
        totalActiveTicks++;
        
        std::this_thread::sleep_for(std::chrono::duration<float>(delayPerExec));

        // Check if quantum has expired
        if (currentQuantumTime >= quantumSlice) {
            // Process quantum expired, notify scheduler
            if (processCompletionCallback && !currentProcess->isFinished()) {
                processCompletionCallback(currentProcess);
            }
            preemptProcess();
        }
    }
}

void CoreWorker::preemptProcess() {
    std::lock_guard<std::mutex> lock(coreMutex);
    currentProcess.reset();
    processAssigned = false;
    currentQuantumTime = 0;
}

bool CoreWorker::needsPreemption() const {
    return quantumSlice > 0 && currentProcess && !currentProcess->isFinished() && 
           currentQuantumTime >= quantumSlice;
}


void CoreWorker::finishProcess() {
    std::lock_guard<std::mutex> lock(coreMutex);
    currentProcess.reset(); // Reset the current process
    processAssigned = false; // No more process assigned
}

bool CoreWorker::isAvailable() {
    std::lock_guard<std::mutex> lock(coreMutex);
    return !processAssigned; // Core is available if no process is assigned
}

bool CoreWorker::isAssignedProcess() {
	std::lock_guard<std::mutex> lock(coreMutex);
	return processAssigned; // Has a process assigned
}

int CoreWorker::getID() {
    return id;
}

void CoreWorker::start() {
    running = true;
    coreThread = std::thread(&CoreWorker::run, this); // Start the core thread
}

void CoreWorker::stop() {
    running = false;
    {
        std::lock_guard<std::mutex> lock(coreMutex);
        running = false;
    }
    if (coreThread.joinable()) {
        coreThread.join();
    }
}

void CoreWorker::run() {
    // Core thread loop
    while (true) {
        {
            std::lock_guard<std::mutex> lock(coreMutex);
            if (!running) {
                break;
            }
        }
        totalCPUTicks++;
        if (processAssigned) {
            runProcess();
        }
        else {
            totalIdleTicks++;
            // TODO: might need to add delay here
        }
    }
}

// Set the process completion callback
void CoreWorker::setProcessCompletionCallback(std::function<void(std::shared_ptr<Process>)> callback) {
    std::lock_guard<std::mutex> lock(coreMutex);
    processCompletionCallback = callback;
}

std::vector<long long> CoreWorker::getStats() {
    return { totalCPUTicks, totalActiveTicks, totalIdleTicks };
}
