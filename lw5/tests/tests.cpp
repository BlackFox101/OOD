#pragma once
#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"

#include "../HtmlEditor/CImageSize.h"
#include "../HtmlEditor/Image.h"
#include "../HtmlEditor/Paragraph.h"
#include "../HtmlEditor/CConstDocumentItem.h"
#include "../HtmlEditor/CDocumentItem.h"
#include "../HtmlEditor/CChangeStringCommand.h"
#include "../HtmlEditor/CResizeImageCommand.h"
#include "../HtmlEditor/CInsertDocumentItemCommand.h"
#include "../HtmlEditor/CDeleteDocumentItemCommand.h"
#include "../HtmlEditor/Document.h"
#include <filesystem>

//CHECK(true);
//REQUIRE(true);
//CHECK_THROWS();
//CHECK_NOTHROW();

using namespace std;

bool operator==(const CImageSize& left, const CImageSize& right)
{
	return left.GetWidth() == right.GetWidth()
		&& left.GetHeight() == right.GetHeight();
}

TEST_CASE("CImageSize")
{
	WHEN("Checking create")
	{
		CHECK_NOTHROW(CImageSize(100, 1));
		CHECK_THROWS(CImageSize(101, 1));
		CHECK_THROWS(CImageSize(0, 1));
		CHECK_NOTHROW(CImageSize(1, 1));

		CHECK_NOTHROW(CImageSize(1, 100));
		CHECK_THROWS(CImageSize(1, 101));
		CHECK_THROWS(CImageSize(1, 0));
		CHECK_NOTHROW(CImageSize(1, 1));
	}

	WHEN("Check values")
	{
		CImageSize imageSize(100, 1);
		CHECK(imageSize.GetWidth() == 100);
		CHECK(imageSize.GetHeight() == 1);
	}
}

TEST_CASE("Image")
{
	CHistory histoty;
	WHEN("Create")
	{
		Path path("../image.jpg");
		Image image(histoty, path, 100, 1);
		CHECK(image.GetWidth() == 100);
		CHECK(image.GetHeight() == 1);
	}

	WHEN("Create with missing file")
	{
		Path path("../image1.jpg");
		CHECK_THROWS(Image(histoty, path, 100, 1));
	}

	WHEN("Create with unsupported extinsion file")
	{
		Path path("../image.jpg1");
		CHECK_THROWS(Image(histoty, path, 100 ,1));
	}
}

TEST_CASE("Paragraph")
{
	CHistory histoty;
	WHEN("Create and check values")
	{
		Paragraph paragraph(histoty, "text");
		CHECK(paragraph.GetText() == "text");
		paragraph.SetText("12345");
		CHECK(paragraph.GetText() == "12345");
	}
}

TEST_CASE("CConstDocumentItem")
{
	CHistory histoty;
	auto paragraph = make_shared<Paragraph>(histoty, "text");

	Path path("../image.jpg");
	auto image = make_shared<Image>(histoty, path, 100, 1);

	WHEN("Create with paragraph")
	{
		CConstDocumentItem constDocumentItem(paragraph);
		CHECK(constDocumentItem.GetParagraph() == paragraph);
		CHECK(constDocumentItem.GetImage() == nullptr);
	}

	WHEN("Create with image")
	{
		CConstDocumentItem constDocumentItem(image);
		CHECK(constDocumentItem.GetParagraph() == nullptr);
		CHECK(constDocumentItem.GetImage() == image);
	}
}

TEST_CASE("CDocumentItem")
{
	CHistory histoty;
	auto paragraph = make_shared<Paragraph>(histoty, "text");

	Path path("../image.jpg");
	auto image = make_shared<Image>(histoty, path, 100, 1);

	WHEN("Create with paragraph")
	{
		CDocumentItem constDocumentItem(paragraph);

		auto sharedParagreph = constDocumentItem.GetParagraph();
		CHECK(sharedParagreph == paragraph);
		CHECK(constDocumentItem.GetImage() == nullptr);

		sharedParagreph->SetText("new text");
		CHECK(sharedParagreph->GetText() == paragraph->GetText());
	}

	WHEN("Create with image")
	{
		CDocumentItem constDocumentItem(image);
		auto sharedImage = constDocumentItem.GetImage();
		CHECK(constDocumentItem.GetParagraph() == nullptr);
		CHECK(sharedImage == image);

		CImageSize newImageSize(50, 10);
		sharedImage->Resize(newImageSize);
		CHECK(sharedImage->GetWidth() == image->GetWidth());
		CHECK(sharedImage->GetHeight() == image->GetHeight());
	}
}

TEST_CASE("CChangeStringCommand")
{
	WHEN("Execute and UnExecute command")
	{
		string str1 = "string 1";
		string str2 = "string 2";

		CChangeStringCommand changeStrcommand(str1, str2);
		changeStrcommand.Execute();
		CHECK(str1 == "string 2");

		changeStrcommand.Unexecute();

		CHECK(str1 == "string 1");
	}

	WHEN("Double Execute command")
	{
		string str1 = "string 1";
		string str2 = "string 2";

		CChangeStringCommand changeStrcommand(str1, str2);

		changeStrcommand.Execute();
		CHECK(str1 == "string 2");
		changeStrcommand.Execute();
		CHECK(str1 == "string 2");
	}

	WHEN("Double UnExecute command")
	{
		string str1 = "string 1";
		string str2 = "string 2";

		CChangeStringCommand changeStrcommand(str1, str2);
		changeStrcommand.Execute();
		CHECK(str1 == "string 2");

		changeStrcommand.Unexecute();
		CHECK(str1 == "string 1");
		changeStrcommand.Unexecute();
		CHECK(str1 == "string 1");
	}
}

TEST_CASE("CResizeImageCommand")
{
	WHEN("Execute and UnExecute command")
	{
		CImageSize size1(50, 100);
		CImageSize size2(70, 20);
		CResizeImageCommand resizeImageCommand(size1, size2);

		resizeImageCommand.Execute();
		CHECK(size1 == CImageSize(70, 20));
		resizeImageCommand.Unexecute();
		CHECK(size1 == CImageSize(50, 100));
	}

	WHEN("Double Execute command")
	{
		CImageSize size1(50, 100);
		CImageSize size2(70, 20);
		CResizeImageCommand resizeImageCommand(size1, size2);

		resizeImageCommand.Execute();
		CHECK(size1 == CImageSize(70, 20));
		resizeImageCommand.Execute();
		CHECK(size1 == CImageSize(70, 20));
	}

	WHEN("Double UnExecute command")
	{
		CImageSize size1(50, 100);
		CImageSize size2(70, 20);
		CResizeImageCommand resizeImageCommand(size1, size2);
		resizeImageCommand.Execute();
		CHECK(size1 == CImageSize(70, 20));

		resizeImageCommand.Unexecute();
		CHECK(size1 == CImageSize(50, 100));
		resizeImageCommand.Unexecute();
		CHECK(size1 == CImageSize(50, 100));
	}
}

TEST_CASE("CInsertDocumentItemCommand")
{
	CHistory histoty;
	auto paragraph = make_shared<Paragraph>(histoty, "text");
	WHEN("Execute and UnExecute command")
	{
		vector<shared_ptr<CDocumentItem>> items;
		CDocumentItem constDocumentItem(paragraph);
		auto newItem = make_shared<CDocumentItem>(constDocumentItem);

		CInsertDocumentItemCommand insertCommand(items, newItem, 0);
		CHECK(items.size() == 0);
		insertCommand.Execute();
		CHECK(items.size() == 1);
		CHECK(items[0] == newItem);
		insertCommand.Unexecute();
		CHECK(items.size() == 0);
	}

	WHEN("Double Execute command")
	{
		vector<shared_ptr<CDocumentItem>> items;
		CDocumentItem constDocumentItem(paragraph);
		auto newItem = make_shared<CDocumentItem>(constDocumentItem);

		CInsertDocumentItemCommand insertCommand(items, newItem, 0);
		insertCommand.Execute();
		CHECK(items.size() == 1);
		CHECK(items[0] == newItem);
		insertCommand.Execute();
		CHECK(items.size() == 1);
		CHECK(items[0] == newItem);
	}

	WHEN("Double UnExecute command")
	{
		vector<shared_ptr<CDocumentItem>> items;
		CDocumentItem constDocumentItem(paragraph);
		auto newItem = make_shared<CDocumentItem>(constDocumentItem);

		CInsertDocumentItemCommand insertCommand(items, newItem, 0);
		insertCommand.Execute();
		insertCommand.Unexecute();
		CHECK(items.size() == 0);
		insertCommand.Unexecute();
		CHECK(items.size() == 0);
	}
}

TEST_CASE("CDeleteDocumentItemCommand")
{
	CHistory histoty;
	auto paragraph = make_shared<Paragraph>(histoty, "text");

	WHEN("Execute and UnExecute command")
	{
		vector<shared_ptr<CDocumentItem>> items;
		CDocumentItem constDocumentItem(paragraph);
		auto newItem = make_shared<CDocumentItem>(constDocumentItem);
		items.emplace(items.begin(), newItem);

		auto deletedItem = items[0];
		CDeleteDocumentItemCommand deleteCommand(items, deletedItem, 0);
		CHECK(items.size() == 1);
		CHECK(items[0] == deletedItem);
		deleteCommand.Execute();
		CHECK(items.size() == 0);
		deleteCommand.Unexecute();
		CHECK(items.size() == 1);
		CHECK(items[0] == deletedItem);
	}

	WHEN("Double Execute command")
	{
		vector<shared_ptr<CDocumentItem>> items;
		CDocumentItem constDocumentItem(paragraph);
		auto newItem = make_shared<CDocumentItem>(constDocumentItem);
		items.emplace(items.begin(), newItem);

		auto deletedItem = items[0];
		CDeleteDocumentItemCommand deleteCommand(items, deletedItem, 0);
		deleteCommand.Execute();
		deleteCommand.Execute();
		CHECK(items.size() == 0);
	}

	WHEN("Double UnExecute command")
	{
		vector<shared_ptr<CDocumentItem>> items;
		CDocumentItem constDocumentItem(paragraph);
		auto newItem = make_shared<CDocumentItem>(constDocumentItem);
		items.emplace(items.begin(), newItem);

		auto deletedItem = items[0];
		CDeleteDocumentItemCommand deleteCommand(items, deletedItem, 0);
		deleteCommand.Execute();
		deleteCommand.Unexecute();
		deleteCommand.Unexecute();
		CHECK(items.size() == 1);
		CHECK(items[0] == deletedItem);
	}
}

TEST_CASE("CHistory")
{
	WHEN("Create history")
	{
		CHistory history;
		CHECK(history.CanUndo() == false);
		CHECK(history.CanRedo() == false);
	}

	WHEN("Add command to history")
	{
		CHistory history;

		string str1 = "string 1";
		string str2 = "string 2";
		CChangeStringCommand changeStrcommand(str1, str2);

		history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(changeStrcommand));
		CHECK(str1 == "string 2");
		CHECK(history.CanUndo() == true);
	}

	WHEN("Undo")
	{
		CHistory history;

		string str1 = "string 1";
		string str2 = "string 2";
		CChangeStringCommand changeStrcommand(str1, str2);
		history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(changeStrcommand));
		history.Undo();
		CHECK(str1 == "string 1");
		CHECK(history.CanUndo() == false);
		CHECK_THROWS(history.Undo());
	}

	WHEN("Redo")
	{
		CHistory history;

		string str1 = "string 1";
		string str2 = "string 2";
		CChangeStringCommand changeStrcommand(str1, str2);
		history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(changeStrcommand));
		history.Undo();
		history.Redo();
		CHECK(str1 == "string 2");
		CHECK(history.CanRedo() == false);
		CHECK_THROWS(history.Redo());
	}

	WHEN("Check max command in history")
	{
		string str1 = "string 1";
		string str2 = "string 2";
		CChangeStringCommand changeStrcommand(str1, str2);

		CHistory history;
		for (size_t i = 0; i < 11; i++)
		{
			history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(changeStrcommand));
		}

		int counter = 0;
		while (history.CanUndo())
		{
			history.Undo();
			counter++;
		}
		CHECK(counter == 10);
	}
}

TEST_CASE("Document")
{
	WHEN("Create Document")
	{
		Document document;
		CHECK(document.GetItemsCount() == 0);
		CHECK(document.CanUndo() == false);
		CHECK(document.CanRedo() == false);
		CHECK(document.GetTitle() == "New document");
		CHECK_THROWS(document.GetItem(0));
	}

	WHEN("Insert Paragraph")
	{
		Document document;
		document.InsertParagraph("Text");

		CHECK(document.GetItemsCount() == 1);
		shared_ptr<CDocumentItem> item;
		CHECK_NOTHROW(item = document.GetItem(0));
		CHECK(item->GetParagraph()->GetText() == "Text");
	}

	WHEN("Insert Image")
	{
		Document document;
		Path path("../image.jpg");
		document.InsertImage(path, 100, 50);

		CHECK(document.GetItemsCount() == 1);
		shared_ptr<CDocumentItem> item;
		CHECK_NOTHROW(item = document.GetItem(0));
		auto image = item->GetImage();
		CHECK(image->GetWidth() == 100);
		CHECK(image->GetHeight() == 50);
	}

	WHEN("Delete Item")
	{
		Document document;
		document.InsertParagraph("Text");
		CHECK(document.GetItemsCount() == 1);
		CHECK_THROWS(document.DeleteItem(1));
		CHECK_NOTHROW(document.DeleteItem(0));
		CHECK(document.GetItemsCount() == 0);
	}

	WHEN("Set Title")
	{
		Document document;
		document.SetTitle("new title");
		CHECK(document.GetTitle() == ("new title"));
	}

	WHEN("SetTitle Undo Redo")
	{
		Document document;
		document.SetTitle("new title");
		CHECK(document.CanUndo());
		CHECK_NOTHROW(document.Undo());
		CHECK(document.GetTitle() == "New document");
		CHECK(document.CanRedo());
		CHECK_NOTHROW(document.Redo());
		CHECK(document.GetTitle() == "new title");
	}

	WHEN("InsertParagraph Undo Redo")
	{
		Document document;
		document.InsertParagraph("Text");
		CHECK(document.CanUndo());
		CHECK_NOTHROW(document.Undo());
		CHECK(document.GetItemsCount() == 0);
		CHECK(document.CanRedo());
		CHECK_NOTHROW(document.Redo());
		CHECK(document.GetItemsCount() == 1);
		auto item = document.GetItem(0);
		CHECK(item->GetParagraph()->GetText() == "Text");
	}

	WHEN("InsertImage Undo Redo")
	{
		Document document;
		Path path("../image.jpg");
		document.InsertImage(path, 100, 50);
		CHECK(document.CanUndo());
		CHECK_NOTHROW(document.Undo());
		CHECK(document.GetItemsCount() == 0);
		CHECK(document.CanRedo());
		CHECK_NOTHROW(document.Redo());
		CHECK(document.GetItemsCount() == 1);
		auto item = document.GetItem(0);
		auto image = item->GetImage();
		CHECK(image->GetWidth() == 100);
		CHECK(image->GetHeight() == 50);
	}
}