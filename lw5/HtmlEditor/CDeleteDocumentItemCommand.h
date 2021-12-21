#pragma once
#include "CAbstractCommand.h"
#include "CDocumentItem.h"

using namespace std;

class CDeleteDocumentItemCommand : public CAbstractCommand
{
public:
	//TODO: не пеедавать удал€емый элемент, а вз€ть напр€мую
	CDeleteDocumentItemCommand(vector<shared_ptr<CDocumentItem>>& items, size_t position);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	vector<shared_ptr<CDocumentItem>>& m_items;
	shared_ptr<CDocumentItem> m_item;
	size_t m_position;
};

