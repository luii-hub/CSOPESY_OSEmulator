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
* This function performs the necessary setup or initialization.
*/
void initialize();

/**
 * @brief Handles screen-related functionality.
 *
 * This function deals with screen management or related tasks.
 */
void screen();

/**
 * @brief Runs a test on the scheduler.
 *
 * This function executes a test of the system's scheduling functionality.
 */
void scheduler_test();

/**
 * @brief Stops the scheduler.
 *
 * This function stops or halts the scheduler that is currently running.
 */
void scheduler_stop();

/**
 * @brief Runs a utility report.
 *
 * This function executes a report utility function in the system.
 */
void report_until();

/**
 * @brief Clears the screen.
 *
 * This function clears the console or screen output.
 */
void clear();

/**
 * @brief Exits the application.
 *
 * This function gracefully exits the command-line application.
 */
void exit();

// Function declarations
void screenStart(const std::string& name);
void screenResume(const std::string& name);
void screenList();
void screenExit();

extern std::map<std::string, ScreenSession*> sessionMap;

