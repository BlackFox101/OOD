#include "CClient.h"

CPictureDraft CClient::GetDraftByDesigner(IDesigner& designer, std::istream& input)
{
	return designer.CreateDraft(input);
}

void CClient::GetPrintByPainter(IPainter& painter, CPictureDraft draft, ICanvas& canvas)
{
	painter.DrawPicture(draft, canvas);
}