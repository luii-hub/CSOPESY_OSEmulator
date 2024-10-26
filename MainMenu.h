#pragma once


#include "AConsole.h"

class MainMenu : public AConsole
{
public:
	MainMenu();
	~MainMenu();

	void onExecute() override; // Main loop
	void display() override; // Display the screen
	void process() override; // Process the command

private:
	void displayHeader();
	void handleCommand(string command);
	void ltrim(std::string& s); // trim from start
	void rtrim(std::string& s); // trim from end
	void trim(std::string& s);
};

