#pragma once
#ifndef utilities_h
#define utilities_h

#include <string>
#include <stdlib.h>
#include "styles.h"
using namespace std;

/**
 * @brief Greets the user.
 *
 * This function displays a simple greeting to the user. It can be used at the start
 * of the program to welcome users to the application.
 */
void greetUser();

/**
 * @brief Prints the application header.
 *
 * This function displays a stylized header for the command-line interface. It is used
 * to present a visually appealing introduction at the start of the program.
 */
void printHeader();

/**
 * @brief Executes a test of styled functions.
 *
 * This function tests some functions for applying various text styles and colors.
 * It prints sample text using different colors and styles.
 */
void testStyleFunctions();

/**
 * @brief Executes the command input by the user.
 *
 * This function handles the command entered by the user, mapping the command
 * to the appropriate function for execution. It includes various commands such
 * as "initialize", "screen", "scheduler-test", etc.
 *
 * @param command The command string entered by the user.
 */
void executeCommand(string command);

/**
 * @brief Displays help information.
 *
 * This function displays a list of available commands and their descriptions.
 * It serves as a guide for the user to understand what commands are available
 * in the system.
 */
void helpInfo();

/**
 * @brief Returns the current system time as a string.
 *
 * This function retrieves the current time from the system and formats it as a string
 * in the format "MM/DD/YYYY, HH:MM:SS AM/PM".
 *
 * @return The current time as a string.
 */
string currentTime();

#endif // utilities_h
