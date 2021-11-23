#include "CPainter.h"
#include "CShape.h"
#include <memory>

void CPainter::DrawPicture(CPictureDraft& draft, ICanvas& canvas) const
{
	for (size_t i = 0; i < draft.GetShapeCount(); i++)
	{
		std::shared_ptr<CShape> shape = draft.GetShape(i);
		shape->Draw(canvas);
	}
}
