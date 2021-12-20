#include "stdafx.h"
#include "CInsertDocumentItemCommand.h"

CInsertDocumentItemCommand::CInsertDocumentItemCommand(vector<shared_ptr<CDocumentItem>>& items, const shared_ptr<CDocumentItem>& item, size_t position)
	: m_items(items)
	, m_item(item)
	, m_position(position)
{
}

void CInsertDocumentItemCommand::DoExecute()
{
	m_items.emplace(m_items.begin() + m_position, m_item);
}

void CInsertDocumentItemCommand::DoUnexecute()
{
	m_items.erase(m_items.begin() + m_position);
}
