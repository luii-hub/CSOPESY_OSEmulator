#pragma once
#include <chrono>
#include <string>

class Process {
private:
    int id;
    std::string processName;
    int currentInstruction;
    int totalInstructions;
    int core;
    bool finished;
    float memorySize;
    float pageSize;
    int startAddress;   // New member for start address
    int endAddress;     // New member for end address
    std::chrono::time_point<std::chrono::system_clock> creationTime;

public:
    Process();
    Process(std::string name, int id, int totalInstructions, float memorySize, float pageSize);

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

    // New getter methods for memory addresses
    int getStartAddress() const { return startAddress; }
    int getEndAddress() const { return endAddress; }
    
    // New method to set memory addresses
    void setMemoryAddresses(int start, int end) {
        startAddress = start;
        endAddress = end;
    }
};
