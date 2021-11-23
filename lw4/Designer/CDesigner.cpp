#include "CDesigner.h"
#include <string>
#include <iostream>

CPictureDraft CDesigner::CreateDraft(std::istream& input) const
{
	CPictureDraft draft;
	std::string line;

	std::cout << "Available shapes:\n" + m_factory.GetShapesInfo() << std::endl;

	while (std::getline(input, line))
	{
		try
		{
			draft.AddShape(m_factory.CreateShape(line));
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	return draft;
}
