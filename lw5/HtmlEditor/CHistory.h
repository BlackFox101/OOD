#pragma once
#include "stdafx.h"
#include "ICommand.h"

class CHistory
{
public:
	bool CanUndo()const;
	void Undo();
	bool CanRedo()const;
	void Redo();
	void AddAndExecuteCommand(ICommandPtr&& command);

private:
	const int MAX_COMMANDS_IN_HISTORY = 10;
	std::deque<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};

