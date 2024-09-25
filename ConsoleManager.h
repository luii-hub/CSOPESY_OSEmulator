#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <string>
#include <map>
#include <thread>
#include <chrono>
#include <mutex>

// Struct to hold screen information
struct ScreenSession {
    std::string processName;
    int currentLine = 0;      // Initialize currentLine to 0
    int totalLine = 100;      // Initialize totalLine to 100 (or whatever default value)
    std::string timestamp;
    bool isActive = true;     // Initialize isActive to true
};

// ConsoleManager class declaration
class ConsoleManager {
public:
    ConsoleManager();
    void startSession(const std::string& name);
    void resumeSession(const std::string& name);
    void listSessions();
    void terminateSession(const std::string& name);

private:
    std::map<std::string, ScreenSession> sessions;
    std::map<std::string, std::thread> sessionThreads;
    std::mutex sessionMutex;

    void runSession(const std::string& name);
    std::string getCurrentTimestamp();
};

#endif
