#include "stdafx.h"
#include "CChangeStringCommand.h"

CChangeStringCommand::CChangeStringCommand(std::string& currentStr, const std::string& newStr)
	: m_currentStr(currentStr)
	, m_newStr(newStr)
{
}

void CChangeStringCommand::DoExecute()
{
	std::swap(m_currentStr, m_newStr);
}

void CChangeStringCommand::DoUnexecute()
{
	std::swap(m_currentStr, m_newStr);
}
