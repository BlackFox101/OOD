#include "stdafx.h"
#include "Document.h"
#include "Paragraph.h"
#include "CInsertDocumentItemCommand.h"
#include "CChangeStringCommand.h"

using namespace std;

shared_ptr<IParagraph> Document::InsertParagraph(const string& text, optional<size_t> position)
{
	size_t pos = position.value_or(m_items.size());
	if (pos > m_items.size())
	{
		throw invalid_argument("Wrong position");
	}

	shared_ptr<IParagraph> paragrath = make_shared<Paragraph>(m_history, text);
	CDocumentItem documentItem(paragrath);
	m_history.AddAndExecuteCommand(make_unique<CInsertDocumentItemCommand>(m_items, documentItem, pos));
	return paragrath;
}

shared_ptr<IImage> Document::InsertImage(const Path& path, CImageSize& size, optional<size_t> position)
{
	size_t pos = position.value_or(m_items.size());
	if (pos > m_items.size())
	{
		throw invalid_argument("Wrong position");
	}

	shared_ptr<IImage> image = make_shared<Image>(m_history, path, size);
	CDocumentItem documentItem(image);
	m_history.AddAndExecuteCommand(make_unique<CInsertDocumentItemCommand>(m_items, documentItem, pos));
	return image;
	
}

size_t Document::GetItemsCount() const
{
	return m_items.size();
}

CConstDocumentItem Document::GetItem(size_t index) const
{
	if (index >= m_items.size() || index < 0)
	{
		throw out_of_range("Index out of range");
	}

	return m_items[index];
}

CDocumentItem Document::GetItem(size_t index)
{
	if (index >= m_items.size() || index < 0)
	{
		throw out_of_range("Index out of range");
	}

	return m_items[index];
}

void Document::DeleteItem(size_t index)
{
	auto documentItem = GetItem(index);

	m_history.AddAndExecuteCommand(make_unique<CInsertDocumentItemCommand>(m_items, documentItem, index));
}

string Document::GetTitle() const
{
	return m_title;
}

void Document::SetTitle(const string& title)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

bool Document::CanUndo() const
{
	return m_history.CanUndo();
}

bool Document::CanRedo() const
{
	return m_history.CanRedo();
}

void Document::Undo()
{
	m_history.Undo();
}

void Document::Redo()
{
	m_history.Redo();
}

void Document::Save(const Path& path) const
{
	// TODO: make an implementation
}