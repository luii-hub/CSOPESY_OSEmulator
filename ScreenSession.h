#pragma once
#include <string>
#include <thread>
#include <chrono>
#include <ctime>

class ScreenSession {
private:
    std::string name;
    std::thread sessionThread;
    bool isRunning;
    int totalInstructions;
    int currentInstruction;
    std::string timestamp;

    // Helper method to get the current time in the desired format
    std::string getCurrentTime();

    // Thread function that runs the screen session
    void runSession();

public:
    // Constructor and Destructor
    ScreenSession(const std::string& sessionName);
    ~ScreenSession();

    // Methods to control the session
    void start();
    void resume();
    bool isSessionRunning() const;
    std::string getName() const;
    std::string getTimestamp() const;
};

