#pragma once
#include "CAbstractCommand.h"

class CChangeStringCommand : public CAbstractCommand
{
public:
	CChangeStringCommand(std::string& currentStr, const std::string& newStr);
protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::string& m_currentStr, m_newStr;
};