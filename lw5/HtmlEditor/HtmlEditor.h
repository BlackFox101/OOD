#pragma once
#include "stdafx.h"
#include "Document.h"
#include "CMenu.h"

using namespace std;

class HtmlEditor
{
public:
	HtmlEditor();
	void Start();

private:
	typedef void (HtmlEditor::* MenuHandler)(istream& in);

	void AddMenuItem(const string& shortcut, const string& description, MenuHandler handler);

	void InsertParagraph(istream& in);
	void InsertImage(istream& in);
	void SetTitle(istream& in);
	void List(istream&);
	void Help(istream&);
	void Undo(istream&);
	void Redo(istream&);
	void ReplaceText(istream& in);
	void ResizeImage(istream& in);
	void DeleteItem(istream& in);
	void Save(istream& in);

	CMenu m_menu;
	unique_ptr<IDocument> m_document;

	static optional<size_t> GetPosition(string stringPosition);
};