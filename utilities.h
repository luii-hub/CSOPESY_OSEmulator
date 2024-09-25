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
 * This function displays a simple greeting to the user.
 */
void greetUser();

/**
 * @brief Prints the application header.
 *
 * This function displays the header for the command-line interface.
 */
void printHeader();

/**
 * @brief Executes a test of styled functions.
 *
 * This function tests some functions for styling.
 */
void testStyleFunctions();

/**
 * @brief Executes the command input by the user.
 *
 * This function handles the command entered by the user, passing it
 * to the corresponding process or helper function.
 *
 * @param command The command string entered by the user.
 */
//void executeCommand(std::string command);

/* 
* @brief Displays help information.
*
* This function displays a list of available commands and their descriptions.
*/
void helpInfo();

void executeCommand(string command);

string currentTime();

#endif // utilities_h
