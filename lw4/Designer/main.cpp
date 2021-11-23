#include <iostream>
#include <fstream>
#include "CShapeFactory.h"
#include "CDesigner.h"
#include "CClient.h"

using namespace std;

int main()
{
	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);
	CClient client;
	CPainter painter;

	CPictureDraft draft = client.GetDraftByDesigner(designer, cin);
	cout << "Draft created\n";

	std::ofstream output;
	output.open("picture.svg");

	SVGCanvas canvas(output);
	client.GetPrintByPainter(painter, draft, canvas);
}