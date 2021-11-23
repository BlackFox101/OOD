#pragma once
#include "CDesigner.h"
#include "CPainter.h"
#include <istream>

class CClient
{
public:
	CPictureDraft GetDraftByDesigner(IDesigner& designer, std::istream& input);
	void GetPrintByPainter(IPainter& painter, CPictureDraft draft, ICanvas& canvas);
};

