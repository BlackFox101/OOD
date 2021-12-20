#include "stdafx.h"
#include "CHistory.h"
#include "ICommand.h"

bool CHistory::CanUndo() const
{
	return m_nextCommandIndex != 0;
}

bool CHistory::CanRedo() const
{
	return m_nextCommandIndex != m_commands.size();
}

void CHistory::Undo()
{
	if (!CanUndo())
	{
		throw std::logic_error("Can't undo");
	}

	m_commands[m_nextCommandIndex - 1]->Unexecute();
	--m_nextCommandIndex;
}

void CHistory::Redo()
{
	if (!CanRedo())
	{
		throw std::logic_error("Can't redo");
	}

	m_commands[m_nextCommandIndex]->Execute();
	++m_nextCommandIndex;
}

void CHistory::AddAndExecuteCommand(ICommandPtr&& command)
{
	if (m_nextCommandIndex < m_commands.size())
	{
		command->Execute();
		++m_nextCommandIndex;
		m_commands.resize(m_nextCommandIndex);
		m_commands.back() = move(command);
	}
	else
	{
		m_commands.emplace_back(nullptr);

		try
		{
			command->Execute();
			m_commands.back() = move(command);
			++m_nextCommandIndex;
			if (m_nextCommandIndex > MAX_COMMANDS_IN_HISTORY)
			{
				m_commands.erase(m_commands.begin());
				m_nextCommandIndex--;
			}
		}
		catch (...)
		{
			m_commands.pop_back();
			throw;
		}
	}
}