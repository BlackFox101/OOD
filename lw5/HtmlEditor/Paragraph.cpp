#include "stdafx.h"
#include "Paragraph.h"
#include "CChangeStringCommand.h"

Paragraph::Paragraph(CHistory& history, const std::string& text)
	: m_history(history)
	, m_text(text)
{
}

std::string Paragraph::GetText() const
{
	return m_text;
}

void Paragraph::SetText(const std::string& text)
{
	m_history.AddAndExecuteCommand(std::make_unique<CChangeStringCommand>(m_text, text));
}
