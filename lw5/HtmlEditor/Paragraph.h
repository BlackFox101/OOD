#pragma once
#include "IParagraph.h"
#include "CHistory.h"

class Paragraph : public IParagraph
{
public:
	Paragraph(CHistory& history, const std::string& text);
	std::string GetText() const;
	void SetText(const std::string& text);

private:
	CHistory& m_history;
	std::string m_text;
};

