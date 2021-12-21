#pragma once
#include "stdafx.h"
#include "ICommand.h"

class IHistory
{
public:
	virtual void AddAndExecuteCommand(ICommandPtr&& command) = 0;
};

class CHistory : public IHistory
{
public:
	bool CanUndo() const;
	void Undo();
	bool CanRedo() const;
	void Redo();
	void AddAndExecuteCommand(ICommandPtr&& command) override;

private:
	const int MAX_COMMANDS_IN_HISTORY = 10;
	std::deque<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};

