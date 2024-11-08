#pragma once
#include <string>

using namespace std;

class AConsole
{
public:
	AConsole(const string& name);
	virtual ~AConsole();

	string getName();

	virtual void onExecute() = 0;
	virtual void display() = 0;
	virtual void process() = 0;

private:
	string name;
};

