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
	shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		optional<size_t> position = nullopt) override;

	size_t GetItemsCount() const;
	shared_ptr<CConstDocumentItem> GetItem(size_t index) const;
	shared_ptr<CDocumentItem> GetItem(size_t index);

	void DeleteItem(size_t index);
	string GetTitle() const;
	void SetTitle(const string& title);
	bool CanUndo() const;
	void Undo();
	bool CanRedo() const;
	void Redo();
	void Save(const Path& path) const;

private:
	string m_title = "New document";
	vector<shared_ptr<CDocumentItem>> m_items;
	CHistory m_history;
	const std::string IMAGE_DIRECTORY_NAME = "images";

	static string EncodingHTMLCharacters(const string& str);
};