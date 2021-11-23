#pragma once
#include "CPictureDraft.h"
#include "CShapeFactory.h"

class IDesigner
{
public:
	virtual ~IDesigner() = default;
	virtual CPictureDraft CreateDraft(std::istream& input) const = 0;
};

class CDesigner : public IDesigner
{
public:
	CDesigner(IShapeFactory& factory)
		: m_factory(factory)
	{}

	CPictureDraft CreateDraft(std::istream& input) const override;
private:
	IShapeFactory& m_factory;
};