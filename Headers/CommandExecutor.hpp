#pragma once

#include <string>
#include <unordered_map>
#include <functional>

//=================================================================================================

namespace pr
{
	class CommandExecutor
	{
	public:
		typedef std::function<void(void)> Command;
		typedef std::unordered_map<std::string, Command> Commands;

		CommandExecutor();
		~CommandExecutor();
		void execute(const std::string& commandName) const;
		void addCommand(const std::string& commandName, const Command& command);
		void removeCommand(const std::string& commandName);
		const Commands& getCommands() const;

	private:
		Commands commands;
	};
}