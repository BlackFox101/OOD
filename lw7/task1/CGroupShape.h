#pragma once
#include "IGroupShape.h"
#include "CGroupOutlineStyle.h"
#include "CGroupFillStyle.h"

class CGroupShape
	: public IGroupShape
	, public std::enable_shared_from_this<CGroupShape>
	, public IFillStyleEnumerator
	, public IOutlineStyleEnumarator
{
	struct CreateTag
	{
		explicit CreateTag() = default;
	};
public:
	CGroupShape(std::shared_ptr<IShape> shape/*, CreateTag*/);

	//static std::shared_ptr<IGroupShape> Create(std::shared_ptr<IShape> shape);

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

	void SetParent(std::shared_ptr<const IGroupShape> parent) override;
	std::shared_ptr<const IGroupShape> GetParent() const override;

	void Draw(ICanvas& canvas) override;

	void EnumarateFillStyles(FillStyleCallback callback) const override;
	void EnumarateOutlineStyles(OutlineStyleCallback callback) const override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<const IGroupShape> m_parent = nullptr;
	std::shared_ptr<IOutlineStyle> m_outlineStyle = nullptr;//std::make_shared<CGroupOutlineStyle>(GetGroup());
	std::shared_ptr<IStyle> m_fillStyle = nullptr;//std::make_shared<CGroupFillStyle>(GetGroup());

	bool CanInsertShape(std::shared_ptr<const IShape> shape) const;
	bool IsExistShape(std::shared_ptr<const IShape> shape) const;
};