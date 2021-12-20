#include "stdafx.h"
#include "CDeleteDocumentItemCommand.h"

CDeleteDocumentItemCommand::CDeleteDocumentItemCommand(vector<shared_ptr<CDocumentItem>>& items, const shared_ptr<CDocumentItem>& item, size_t position)
	: m_items(items)
	, m_item(item)
	, m_position(position)
{
}

void CDeleteDocumentItemCommand::DoExecute()
{
	m_items.erase(m_items.begin() + m_position);
}

void CDeleteDocumentItemCommand::DoUnexecute()
{
	m_items.emplace(m_items.begin() + m_position, m_item);
}
