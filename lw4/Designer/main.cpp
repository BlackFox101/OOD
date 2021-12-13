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

	ofstream output;
	output.open("picture.svg");

	SVGCanvas canvas(output);
	client.GetPrintByPainter(painter, draft, canvas);
	/*
	ellipse 100 100 50 30 red
	triangle 10 10 30 10 15 30 green
	rectangle 300 400 400 300 red
	regularPolygon 5 200 200 40 blue
	*/
}