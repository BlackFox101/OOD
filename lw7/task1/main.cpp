#include <fstream>
#include "stdafx.h"
#include "CSlide.h"
#include "SVGCanvas.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CGroupShape.h"
#include "CEllipse.h"

using namespace std;

int main()
{
    /*shared_ptr<IShape> foundation = make_shared<CRectangle>(Point{100, 100}, Point{300, 200});
    foundation->GetFillStyle()->SetColor(0x573d00);
    shared_ptr<IShape> tube = make_shared<CRectangle>(Point{ 270, 50 }, Point{ 290, 100 });
    tube->GetFillStyle()->SetColor(0xfc0303);
    shared_ptr<IShape> roof = make_shared<CTriangle>(Point{ 100, 100 }, Point{ 300, 100 }, Point{ 200, 50 });
    roof->GetFillStyle()->SetColor(0xA8A8A8);

    shared_ptr<CGroupShape> group = make_shared<CGroupShape>(foundation);
    group->InsertShape(tube);
    group->InsertShape(roof);

    group->SetFrame(RectD{ Point{ 100, 100 }, 200, 100 });
    group->GetFillStyle()->SetColor(0xFF00FF);*/

    shared_ptr<IShape> foundation = make_shared<CRectangle>(Point{ 100, 100 }, Point{ 300, 200 });
    shared_ptr<CGroupShape> group = make_shared<CGroupShape>(foundation);

    //CSlide slide(1000, 1000);
    //slide.InsertShape(group);
    

    //ofstream output("../picture.svg");
    //SVGCanvas canvas(output);
    //slide.Draw(canvas);
}