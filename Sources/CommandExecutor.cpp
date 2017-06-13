#include "CommandExecutor.hpp"

//=================================================================================================

pr::CommandExecutor::CommandExecutor()
{
}

//=================================================================================================

pr::CommandExecutor::~CommandExecutor()
{
}

//=================================================================================================

void pr::CommandExecutor::execute(const std::string& commandName) const
{
	if (functions.find(commandName) == functions.end())
		return;

	functions.at(commandName)();
}

//=================================================================================================

void pr::CommandExecutor::addCommand(const std::string& commandName, const Command& command)
{
	functions.emplace(commandName, command);
}

//=================================================================================================

void pr::CommandExecutor::removeCommand(const std::string& commandName)
{
	if (functions.find(commandName) == functions.end())
		return;

	functions.erase(commandName);
}