#include <iostream>

#include "MainMenu.h"
#include "ConsoleManager.h"
#include "styles.h"

extern ConsoleManager consoleManager;

MainMenu::MainMenu()
	: AConsole("MAIN_MENU"){
}

MainMenu::~MainMenu(){

}

void MainMenu::onExecute(){
	display(); 
	process();
}

void MainMenu::display(){
	displayHeader();
}

void MainMenu::process() {
    string command;
    while (true) {
        cout << "root:\\> ";
        getline(cin, command);
        handleCommand(command);
        cout << endl;
    }
}

void MainMenu::displayHeader(){
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

    string welcome = "Hello, Welcome to CSOPESY command line!";
    string guide = "Type 'help' to see a list of commands";
    cout << color_green(welcome) << endl;  // Print welcome message in green
    cout << color_bright_yellow(guide) << endl;  // Print guide message in yellow
}

void MainMenu::handleCommand(string command) {
    if (command == "exit") {
        cout << "Exiting the program..." << endl;
        exit(0);

    } else if (command == "initialize" && !consoleManager.getConfigurationManager().isInitialized()) 
    {
        consoleManager.setInitialized();

	} else if (consoleManager.getConfigurationManager().isInitialized()) 
    {
        if (command == "clear" || command == "cls") 
        {
            system("cls");

        } else if (command.substr(0,6) == "screen") 
        {
            if (command == "screen -ls") {
                consoleManager.displayStatus();
            }
            else if (command.substr(0, 9) == "screen -s")
            {
                string processName = command.substr(10);
                trim(processName);
                if (processName.empty()) { // if the process name is empty
                    cout << "Command not recognized! Please provide a process name." << endl;
            }

                // if the process name is not empty
                else 
                { 
                    // if the process does not exist, create process
                    if (!consoleManager.getResourceManager().processExists(processName)) {
                        consoleManager.createProcessScreen(processName);
                    }
                    else { // if the process already exists
                        cout << "Process already exists or has existed. Please provide a different name." << endl;
                    }
                   
                }
            }

            else if (command.substr(0,9) == "screen -r")
            {
                string processName = command.substr(10);
                trim(processName);

                // if the process name is empty
                if (processName.empty()) 
                { 
                    cout << "Command not recognized! Please provide a process name." << endl;
                }

                else {
                    if (consoleManager.isProcessFinished(processName)) { // if the process is finished, there will be no screen
                        cout << "Process " << processName << " not found." << endl;
                    }
                    else { // if the process is not finished, switch to the screen
                        consoleManager.switchScreen("PROCESS_SCREEN_" + processName);
                    }
                }
            }

        } else if (command.substr(0, 9) == "scheduler") {
            if (command.substr(10) == "test") { 
                consoleManager.getResourceManager().startSchedulerTest();
            }

            else if (command.substr(10) == "stop") { 
                consoleManager.getResourceManager().stopSchedulerTest();
            } 

            else {
                cout << "Invalid command.Please try again." << endl;
            }

        } else if (command == "report-util") {
            consoleManager.getResourceManager().saveReport();

		} else if (command == "help") {
			cout << "\nCommands:" << endl;
			cout << "clear/cls - Clear the screen" << endl;
			cout << "screen -ls - List all screens" << endl;
			cout << "screen -s [processName] - Create a new process screen" << endl;
			cout << "scheduler-test - Start the scheduler test" << endl;
			cout << "scheduler-stop - Stop the scheduler test" << endl;
			cout << "report-util - Save the report" << endl;
			cout << "exit - Exit the program" << endl;
		}
		else if (command == "process-smi") {
            consoleManager.getResourceManager().displayProcessSmi();
        }
        else {
            cout << "Invalid command. Please try again." << endl;
        }

    } else {
        cout << "You must initialize the program first." << endl;
    }
}

void MainMenu::ltrim(string& s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
        return !isspace(ch);
        }));
}

void MainMenu::rtrim(string& s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
        return !isspace(ch);
        }).base(), s.end());
}

void MainMenu::trim(string& s) {
    ltrim(s);
    rtrim(s);
}