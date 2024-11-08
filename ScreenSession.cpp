#include "ScreenSession.h"
#include <iostream>
#include <ctime>

ScreenSession::ScreenSession(const std::string& sessionName)
    : name(sessionName), isRunning(false), totalInstructions(100), currentInstruction(0) {
    timestamp = getCurrentTime();
}

ScreenSession::~ScreenSession() {
    if (sessionThread.joinable()) {
        sessionThread.join();  // Ensure the thread finishes before destruction
    }
}

// Helper function to get the current time in (MM/DD/YYYY, HH:MM:SS AM/PM) format
std::string ScreenSession::getCurrentTime() {
    time_t now = time(0);
    tm localtm;
    localtime_s(&localtm, &now);
    char buffer[100];
    strftime(buffer, 100, "%m/%d/%Y, %I:%M:%S %p", &localtm);
    return std::string(buffer);
}

// Method to run the session (in a separate thread)
void ScreenSession::runSession() {
    isRunning = true;
    while (currentInstruction < totalInstructions) {
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate work
        currentInstruction++;
        //std::cout << "Process: " << name << " | Instruction: " << currentInstruction
         //   << "/" << totalInstructions << std::endl;
    }
    isRunning = false;
    std::cout << "Screen session " << name << " completed." << std::endl;
}

void ScreenSession::start() {
    if (!isRunning) {
        sessionThread = std::thread(&ScreenSession::runSession, this);  // Start in a new thread
        sessionThread.detach();  // Detach thread so it runs in the background
        std::cout << "Session " << name << " started at " << timestamp << std::endl;
    }
    else {
        std::cout << "Session " << name << " is already running." << std::endl;
    }
}

void ScreenSession::resume() {
    if (isRunning) {
        std::cout << "Resuming session: " << name << std::endl;
    }
    else {
        std::cout << "Session " << name << " is not running." << std::endl;
    }
}

bool ScreenSession::isSessionRunning() const {
    return isRunning;
}

std::string ScreenSession::getName() const {
    return name;
}

std::string ScreenSession::getTimestamp() const {
    return timestamp;
}

