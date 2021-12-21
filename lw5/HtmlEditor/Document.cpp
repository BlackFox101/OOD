#include "stdafx.h"
#include "Document.h"
#include "Paragraph.h"
#include "CInsertDocumentItemCommand.h"
#include "CChangeStringCommand.h"
#include "CDeleteDocumentItemCommand.h"
#include <fstream>

using namespace std;

shared_ptr<IParagraph> Document::InsertParagraph(const string& text, optional<size_t> position)
{
	size_t pos = position.value_or(m_items.size());
	if (pos > m_items.size())
	{
		throw invalid_argument("Wrong position");
	}

	shared_ptr<IParagraph> paragrath = make_shared<Paragraph>(m_history, text);
	shared_ptr<CDocumentItem> documentItem = make_shared<CDocumentItem>(paragrath);
	m_history.AddAndExecuteCommand(make_unique<CInsertDocumentItemCommand>(m_items, documentItem, pos));
	return paragrath;
}

shared_ptr<IImage> Document::InsertImage(const Path& path, int width, int height, optional<size_t> position)
{
	size_t pos = position.value_or(m_items.size());
	if (pos > m_items.size())
	{
		throw invalid_argument("Wrong position");
	}

	shared_ptr<IImage> image = make_shared<Image>(m_history, path, width, height);
	shared_ptr<CDocumentItem> documentItem = make_shared<CDocumentItem>(image);
	m_history.AddAndExecuteCommand(make_unique<CInsertDocumentItemCommand>(m_items, documentItem, pos));
	return image;
	
}

size_t Document::GetItemsCount() const
{
	return m_items.size();
}

shared_ptr<CConstDocumentItem> Document::GetItem(size_t index) const
{
	if (index >= m_items.size() || index < 0)
	{
		throw out_of_range("Index out of range");
	}

	return m_items[index];
}

shared_ptr<CDocumentItem> Document::GetItem(size_t index)
{
	if (index >= m_items.size() || index < 0)
	{
		throw out_of_range("Index out of range");
	}

	return m_items[index];
}

void Document::DeleteItem(size_t index)
{
	m_history.AddAndExecuteCommand(make_unique<CDeleteDocumentItemCommand>(m_items, index));
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
	setlocale(LC_ALL, "Russian");
	cout << path << endl;
	ofstream html;
	html.open(path.string() + "index.html");
	html << "<!DOCTYPE html>\n";
	html << "<html lang=\"en\">\n";
	html << "<head>\n";
	html << "  <title>" + EncodingHTMLCharacters(GetTitle()) + "</title>\n";
	html << "</head>\n";
	html << "<body>\n";

	for (auto item : m_items)
	{
		html << "  ";

		auto paragraph = item->GetParagraph();
		if (paragraph)
		{
			html << "<p>" << EncodingHTMLCharacters(paragraph->GetText()) << "</p>\n";
			continue;
		}

		auto image = item->GetImage();
		if (image)
		{
			html << "<img src=\"" << EncodingHTMLCharacters(image->GetPath().string()) << "\" "
					"width=\"" << image->GetWidth() << "\" "
					"height=\"" << image->GetHeight() << "\">\n";

			string dir = path.string() + IMAGE_DIRECTORY_NAME + '/';
			Path newPath(dir + image->GetPath().filename().string());
			filesystem::create_directory(dir);
			filesystem::copy_file(image->GetPath(), newPath, filesystem::copy_options::overwrite_existing);
		}
	}
	html << "</body>\n";
	html << "</html>\n";
}

string Document::EncodingHTMLCharacters(const string& str)
{
	string encodingStr;
	for (char item : str)
	{
		switch (item)
		{
		case '<':
			encodingStr += "&lt;";
			continue;
		case '>':
			encodingStr += "&gt;";
			continue;
		case '"':
			encodingStr += "&quot;";
			continue;
		case '\'':
			encodingStr += "&#x60;";
			continue;
		case '&':
			encodingStr += "&amp;";
			continue;
		default:
			encodingStr += item;
		}
	}
	return encodingStr;
}

