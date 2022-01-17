#pragma once
#include "IShape.h"
#include "COutlineStyle.h"
#include "CFillStyle.h"

class CShape : public IShape
{
public:
	std::shared_ptr<IOutlineStyle> GetOutlineStyle() override;
	std::shared_ptr<const IOutlineStyle> GetOutlineStyle() const override;

	std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle() const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	void SetParent(std::shared_ptr<const IGroupShape> parent) override;
	std::shared_ptr<const IGroupShape> GetParent() const override;
private:
	std::shared_ptr<const IGroupShape> m_parent = nullptr;
	std::shared_ptr<IOutlineStyle> m_outlineStyle = std::make_shared<COutlineStyle>();
	std::shared_ptr<IStyle> m_fillStyle = std::make_shared<CFillStyle>();
};