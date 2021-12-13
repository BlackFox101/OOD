#pragma once
#include "CAbstractCommand.h"
#include "CDocumentItem.h"

using namespace std;

class CInsertDocumentItemCommand : public CAbstractCommand
{
public:
	CInsertDocumentItemCommand(vector<CDocumentItem>& items, CDocumentItem& item, size_t position);
protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	vector<CDocumentItem>& m_items;
	CDocumentItem& m_item;
	size_t m_position;
};

