#include <string>
#include "utilities.h"
#include "styles.h"
#include "process.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <chrono>

using namespace std;

void printHeader() {
    cout << color_blue(style_bold(style_blink(R"( 
 _____________________________________________________                                                   
|   _____  _____  ____  _____  ______ _____ __     __ |
|  / ____|/ ____|/ __ \|  __ \|  ____/ ____|\ \   / / |
| | |    | (___ | |  | | |__) | |__  | (___  \ \_/ /  |
| | |     \___ \| |  | |  ___/|  __|  \___ \  \   /   |
| | |____ ____) | |__| | |    | |____ ____) |  | |    |
|  \_____|_____/ \____/|_|    |______|_____/   |_|    |                                                     
 -----------------------------------------------------
    )"))) << endl;
}

void greetUser() {
    string welcome = "Hello, Welcome to CSOPESY command line!";
    string guide = "Type 'help' to see a list of commands";
    cout << color_green(welcome) << endl;
    cout << color_bright_yellow(guide) << endl;
}

void helpInfo() {
    cout << R"(
List of commands:
|-- initialize           : Initialize the system
|-- screen               : Screen management commands
|   |-- screen -ls       : List all sessions
|   |-- screen -s <name> : Start a new screen
|   |-- screen -r <name> : Resume a screen
|-- scheduler-test       : Test the scheduler
|-- scheduler-stop       : Stop the scheduler
|-- report-util          : Generate a report
|-- clear                : Clear the screen
|-- exit                 : Exit the program
)" << endl;
}


void executeCommand(string command) {
    if (command == "initialize") {
		initialize();
	}
    else if (command == "help") {
		helpInfo();
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


std::string currentTime() {
    time_t now = time(0);
    tm localtm;
    localtime_s(&localtm, &now);  // Use localtime_s instead of localtime
    char buffer[100];
    strftime(buffer, 100, "%m/%d/%Y, %I:%M:%S %p", &localtm);
    return std::string(buffer);
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


