#pragma once
#include "CAbstractCommand.h"
#include "CDocumentItem.h"

using namespace std;

class CDeleteDocumentItemCommand : public CAbstractCommand
{
public:
	CDeleteDocumentItemCommand(vector<shared_ptr<CDocumentItem>>& items, const shared_ptr<CDocumentItem>& item, size_t position);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	vector<shared_ptr<CDocumentItem>>& m_items;
	shared_ptr<CDocumentItem> m_item;
	size_t m_position;
};

