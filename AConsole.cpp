#include "AConsole.h"

AConsole::AConsole(const string& name)
{
	this->name = name;
}

AConsole::~AConsole() = default;

string AConsole::getName()
{
	return name;
}