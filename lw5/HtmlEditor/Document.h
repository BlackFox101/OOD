#pragma once
#include "stdafx.h"
#include "IDocument.h"
#include "CHistory.h"

using namespace std;

class Document : public IDocument
{
public:
	shared_ptr<IParagraph> InsertParagraph(const string& text,
		optional<size_t> position = nullopt) override;
	shared_ptr<IImage> InsertImage(const Path& path, CImageSize& size,
		optional<size_t> position = nullopt) override;

	size_t GetItemsCount() const;
	CConstDocumentItem GetItem(size_t index) const;
	CDocumentItem GetItem(size_t index);

	void DeleteItem(size_t index);
	string GetTitle() const;
	void SetTitle(const string& title);
	bool CanUndo() const;
	void Undo();
	bool CanRedo() const;
	void Redo();
	void Save(const Path& path)const;

private:
	string m_title = "New document";
	vector<CDocumentItem> m_items;
	CHistory m_history;
};