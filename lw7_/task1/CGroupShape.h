#pragma once
#include "IGroupShape.h"
#include "CGroupFillStyle.h"
#include "CGroupOutlineStyle.h"
#include "stdafx.h"

class CGroupShape 
	: public IGroupShape
	, public std::enable_shared_from_this<CGroupShape>
{
public:
	CGroupShape(std::shared_ptr<IShape> shape);

	RectD GetFrame() override;
	void SetFrame(const RectD& rect) override;

	std::shared_ptr<IOutlineStyle> GetOutlineStyle() override;
	std::shared_ptr<const IOutlineStyle> GetOutlineStyle() const override;
	std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle() const override;
	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	size_t GetShapesCount() const override;
	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max()) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

	void SetParent(std::shared_ptr<const IGroupShape> parent);
	std::shared_ptr<const IGroupShape> GetParent() const;

	void Draw(ICanvas& canvas) override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<const IGroupShape> m_parent = nullptr;
	std::shared_ptr<IOutlineStyle> m_outlineStyle = nullptr;
	std::shared_ptr<IStyle> m_fillStyle = nullptr;

	bool CanInsertShape(const std::shared_ptr<IShape>& shape) const;
};

