#ifndef process_h
#define process_h
#pragma once
#include <iostream>
#include "styles.h"
#include "utilities.h"
#include <string>
#include <stdlib.h>
#include <map>
#include "ConsoleManager.h"

using namespace std;

/**
 * @brief Initializes the system or application.
 *
 * This function is intended to handle any necessary setup or initialization required
 * by the system. It may include actions such as allocating resources, setting
 * configurations, or starting services.
 */
void initialize();

/**
 * @brief Handles screen-related functionality.
 *
 * This function processes user input related to screen management. It allows
 * the user to start, resume, or list screen sessions using the `ConsoleManager` class.
 */
void screen();

/**
 * @brief Runs a test on the scheduler.
 *
 * This function is intended to test the system's scheduling functionality.
 * It may include tests on how tasks are scheduled, executed, or handled.
 */
void scheduler_test();

/**
 * @brief Stops the scheduler.
 *
 * This function halts the scheduler that is currently running in the system.
 * It could stop background tasks, processes, or jobs that the scheduler manages.
 */
void scheduler_stop();

/**
 * @brief Runs a utility report.
 *
 * This function generates a report or executes a report utility within the system.
 * It may gather data from various sources and compile it into a report format.
 */
void report_until();

/**
 * @brief Clears the console screen.
 *
 * This function clears the contents of the terminal or console. It resets
 * the output display to show a clean screen.
 */
void clear();

/**
 * @brief Exits the application.
 *
 * This function gracefully terminates the command-line application and
 * performs any necessary cleanup before the program exits.
 */
void exit();

/**
 * @brief Starts a screen session with the specified name.
 *
 * This function is a placeholder for managing screen session creation in the system.
 * @param name The name of the screen session.
 */
void screenStart(const std::string& name);

/**
 * @brief Resumes a screen session with the specified name.
 *
 * This function is a placeholder for resuming screen sessions.
 * @param name The name of the screen session.
 */
void screenResume(const std::string& name);

/**
 * @brief Lists all active screen sessions.
 *
 * This function is a placeholder for displaying a list of active screen sessions.
 */
void screenList();

/**
 * @brief Terminates the screen session management.
 *
 * This function is a placeholder for exiting screen session management.
 */
void screenExit();

// Global map to manage screen sessions
extern std::map<std::string, ScreenSession*> sessionMap;

#endif // process_h
