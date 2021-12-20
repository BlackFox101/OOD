#include "stdafx.h"
#include "HtmlEditor.h"

using namespace std;
using namespace placeholders;

HtmlEditor::HtmlEditor()
	: m_document(make_unique<Document>())
{
	AddMenuItem("insertParagraph", "Insert paragraph. Args: <position>|end <paragraph text>", &HtmlEditor::InsertParagraph);
	AddMenuItem("insertImage", "Insert image. Args: <position>|end <width> <height> <file path>", &HtmlEditor::InsertImage);
	AddMenuItem("setTitle", "Changes title. Args: <new title>", &HtmlEditor::SetTitle);
	AddMenuItem("list", "Show document", &HtmlEditor::List);
	AddMenuItem("replaceText", "Replace text. Args: <position> <paragraph text>", &HtmlEditor::ReplaceText);
	AddMenuItem("resizeImage", "Resize image. Args: <position> <width> <height>", &HtmlEditor::ResizeImage);
	AddMenuItem("deleteItem", "Delete item. Args: <position>", &HtmlEditor::DeleteItem);
	AddMenuItem("help", "Help", &HtmlEditor::Help);
	AddMenuItem("undo", "Undo command", &HtmlEditor::Undo);
	AddMenuItem("redo", "Redo undone command", &HtmlEditor::Redo);
	AddMenuItem("save", "Save", &HtmlEditor::Save);
	AddMenuItem("exit", "Exit", &HtmlEditor::Exit);
}

void HtmlEditor::Start()
{
	m_menu.Run();
}

void HtmlEditor::AddMenuItem(const string& shortcut, const string& description, MenuHandler handler)
{
	m_menu.AddItem(shortcut, description, bind(handler, this, _1));
}

void HtmlEditor::InsertParagraph(istream& in)
{
	string position;
	in >> position;
	if (in.fail())
	{
		throw invalid_argument("Not enough arguments");
	}

	string head;
	string tail;
	if (in >> head)
	{
		getline(in, tail);
	}
	string text = head + tail;
	if (text == "")
	{
		throw invalid_argument("Not enough arguments");
	}

	m_document->InsertParagraph(text, GetPosition(position));
}

void HtmlEditor::InsertImage(istream& in)
{
	string position;
	Path filePath;
	int width, height;
	in >> position >> width >> height >> filePath;
	if (in.fail())
	{
		throw invalid_argument("Not enough arguments");
	}

	m_document->InsertImage(filePath, width, height, GetPosition(position));
}

void HtmlEditor::SetTitle(istream& in)
{
	string head;
	string tail;

	if (in >> head)
	{
		getline(in, tail);
	}
	string title = head + tail;

	m_document->SetTitle(title);
}

void HtmlEditor::List(istream&)
{
	cout << "Title: " << m_document->GetTitle() << endl;
	for (size_t i = 0; i < m_document->GetItemsCount(); i++)
	{
		cout << i << ". ";
		auto documentItem = m_document->GetItem(i);
		auto paragraph = documentItem->GetParagraph();
		if (paragraph)
		{
			cout << "Paragraph: " << paragraph->GetText() << endl;
			continue;
		}

		auto image = documentItem->GetImage();
		if (image)
		{
			Path path = image->GetPath();
			cout << "Image: " << image->GetWidth() << " " << image->GetHeight() << " " << path.string()<< endl;
		}
	}
}

void HtmlEditor::Help(istream&)
{
	m_menu.ShowInstructions();
}

void HtmlEditor::Undo(istream&)
{
	try
	{
		m_document->Undo();
	}
	catch (const std::logic_error& e)
	{
		cout << e.what() << endl;
	}
}

void HtmlEditor::Redo(istream&)
{
	try
	{
		m_document->Redo();
	}
	catch (const std::logic_error& e)
	{
		cout << e.what() << endl;
	}
}

void HtmlEditor::ReplaceText(istream& in)
{
	string text;
	int position;
	in >> position;
	getline(in, text);
	if (in.fail() || text == "")
	{
		throw invalid_argument("Not enough arguments");
	}

	auto documentItem = m_document->GetItem(position);
	auto paragraph = documentItem->GetParagraph();
	if (!paragraph)
	{
		throw invalid_argument("This is not a paragraph");
	}

	paragraph->SetText(text);
}

void HtmlEditor::ResizeImage(istream& in)
{
	int position;
	int width, height;
	in >> position >> width >> height;
	if (in.fail())
	{
		throw invalid_argument("Not enough arguments");
	}

	auto documentItem = m_document->GetItem(position);
	auto image = documentItem->GetImage();
	if (!image)
	{
		throw invalid_argument("This is not a image");
	}

	CImageSize size(width, height);
	image->Resize(size);
}

void HtmlEditor::DeleteItem(istream& in)
{
	int position;
	in >> position;
	if (in.fail())
	{
		throw invalid_argument("Not enough arguments");
	}

	m_document->DeleteItem(position);
}

void HtmlEditor::Exit(istream& in)
{
	m_menu.Exit();
}

void HtmlEditor::Save(istream& in)
{
	string head;
	string tail;

	if (in >> head)
	{
		getline(in, tail);
	}
	string str = head + tail;
	if (str == "")
	{
		throw invalid_argument("Not enough arguments");
	}

	Path path(str);
	m_document->Save(path);
}

optional<size_t> HtmlEditor::GetPosition(string stringPosition)
{
	if (stringPosition == "end")
	{
		return nullopt;
	}

	try
	{
		return stoi(stringPosition);
	}
	catch (...)
	{
		throw invalid_argument("Invalid position argument");
	}
}