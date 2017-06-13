#include "CommandExecutor.hpp"

//=================================================================================================

pr::CommandExecutor::CommandExecutor() :
	commands()
{
}

//=================================================================================================

pr::CommandExecutor::~CommandExecutor()
{
}

//=================================================================================================

void pr::CommandExecutor::execute(const std::string& commandName) const
{
	if (commands.find(commandName) == commands.end())
		return;

	commands.at(commandName)();
}

//=================================================================================================

void pr::CommandExecutor::addCommand(const std::string& commandName, const Command& command)
{
	commands.emplace(commandName, command);
}

//=================================================================================================

void pr::CommandExecutor::removeCommand(const std::string& commandName)
{
	if (commands.find(commandName) == commands.end())
		return;

	commands.erase(commandName);
}

const pr::CommandExecutor::Commands& pr::CommandExecutor::getCommands() const
{
	return commands;
}