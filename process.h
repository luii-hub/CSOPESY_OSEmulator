#pragma once
#include <string>
#include <chrono>

// Forward declaration
class Scheduler;

class Process {
    // Declare Scheduler as a friend class to allow access to private members
    friend class Scheduler;

private:
    std::string processName;
    int id;
    int currentInstruction;
    int totalInstructions;
    int core;
    bool finished;
    std::chrono::system_clock::time_point creationTime;
    float memorySize;
    float pageSize;
    int cyclesInCore;

    // Make these functions private since they should only be called by Scheduler
    int getCyclesInCore() const;
    void incrementCyclesInCore();
    void resetCyclesInCore();

public:
    // Constructors
    Process();
    Process(std::string name, int id, int totalInstructions, float memorySize, float pageSize);

    // Public accessor methods
    std::string getName() const;
    int getID() const;
    int getCurrentInstruction() const;
    int getTotalInstructions() const;
    int getRemainingInstructions() const;
    int getCore();
    void setCore(int coreID);
    bool isFinished() const;
    std::string getCreationTime() const;
    float getMemorySize() const;
    float getPageSize() const;
    void execute();
};