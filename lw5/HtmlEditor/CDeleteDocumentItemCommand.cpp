#include "stdafx.h"
#include "CDeleteDocumentItemCommand.h"

CDeleteDocumentItemCommand::CDeleteDocumentItemCommand(vector<shared_ptr<CDocumentItem>>& items, size_t position)
	: m_items(items)
	, m_position(position)
{
	m_item = m_items.at(position);
}

void CDeleteDocumentItemCommand::DoExecute()
{
	m_items.erase(m_items.begin() + m_position);
}

void CDeleteDocumentItemCommand::DoUnexecute()
{
	m_items.emplace(m_items.begin() + m_position, m_item);
}
