#pragma once
#include <memory>
#include <vector>
#include "CShape.h"

class CPictureDraft
{
public:
	void AddShape(std::shared_ptr<CShape>&& shape)
	{
		std::cout << "Add " + shape->GetName() + " to draw.\n";
		m_shapes.push_back(move(shape));
	}

	int GetShapeCount()
	{
		return m_shapes.size();
	}

	std::shared_ptr<CShape> GetShape(int index)
	{
		return m_shapes[index];
	}

private:
	std::vector<std::shared_ptr<CShape>> m_shapes;
};

