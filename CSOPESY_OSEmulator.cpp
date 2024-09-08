// OSEmulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include <stdlib.h>
#include "styles.h"  // Include the header for color and style functions

using namespace std;

// Function prototypes
void intialize();
void screen();
void scheduler_test();
void scheduler_stop();
void report_until();
void clear();
void exit();

void greetUser();
void printHeader();
void executeCommand(string command);
void testStyleFunctions();


int main()
{
    string command;

    //Print ASCII header
    printHeader();

    // Greet the user
    greetUser();

    // Uncomment to test color and style functions (Author Notes: used for test color and style functions. This is not a part of the assignment)
    // testStyleFunctions();

    while (true) {
        cout << color_white("Enter a command: ");
        std::getline(cin, command);
        executeCommand(command);
    }

}

// Function Prototypes
void intialize() {
    cout << "initialize command recognized. Doing something." << endl;
}

void screen() {
    cout << "screen command recognized. Doing something." << endl;
}

void scheduler_test() {
    cout << "scheduler-test command recognized. Doing something." << endl;
}

void scheduler_stop() {
    cout << "scheduler-stop command recognized. Doing something." << endl;
}

void report_until() {
    cout << "report-util command recognized. Doing something." << endl;
}

void clear() {
    cout << "\033[2J\033[H";  // ANSI escape code to clear the screen
    printHeader();
    greetUser();

}

// Test color and style functions
void testStyleFunctions() {
    cout << "Testing color and style functions" << endl;
    cout << color_red("this is red text") << endl;
    cout << color_green("this is green text") << endl;
    cout << color_yellow("this is yellow text") << endl;
    cout << color_blue("this is blue text") << endl;
    cout << color_magenta("this is magenta text") << endl;
    cout << color_cyan("this is cyan text") << endl;
    cout << color_white("this is white text") << endl;
    cout << style_bold("this is bold text") << endl;
    cout << style_underline("this is underlined text") << endl;
    cout << style_blink("this is blinking text") << endl;
    cout << style_dim("this is dim text") << endl;
    cout << style_italic("this is italic text") << endl;
    cout << style_inverse("this is inverse text") << endl;
    cout << style_hidden("this is hidden text") << endl;
    cout << style_strikethrough("this is strikethrough text") << endl;
    cout << style_double_underline("this is double underlined text") << endl;
    cout << style_overline("this is overlined text") << endl;
}

// TODO Implement exit function (Author Notes: This will exit the program close the CLI Application and the program)
void exit() {
    exit(0);
}

void greetUser() {
    string welcome = "Hello, Welcome to CSOPESY command line!";
    string guide = "Type 'exit' to quit, 'clear' to clear the screen";
    cout << color_green(welcome) << endl;
    cout << color_bright_yellow(guide) << endl;
}

// TODO: Implement ASCII header
void printHeader() {
    // ASCII header implementation
    cout << "This is an example header" << endl;
}

void executeCommand(string command) {

    if (command == "initialize") {
        intialize();
    }
    else if (command == "screen") {
        screen();
    }
    else if (command == "scheduler-test") {
        scheduler_test();
    }
    else if (command == "scheduler-stop") {
        scheduler_stop();
    }
    else if (command == "report-util") {
        report_until();
    }
    else if (command == "clear") {
        clear();
    }
    else if (command == "exit") {
        exit();
    }
}
