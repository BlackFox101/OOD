#pragma once
#include "Image.h"
#include "Paragraph.h"

/* Неизменяемый элемент документа */
class CConstDocumentItem
{
public:
	CConstDocumentItem(std::shared_ptr<IImage> image);
	CConstDocumentItem(std::shared_ptr<IParagraph> paragraph);

	// Возвращает указатель на константное изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<const IImage> GetImage() const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<const IParagraph> GetParagraph() const;
	virtual ~CConstDocumentItem() = default;

protected:
	std::shared_ptr<IImage> m_image;
	std::shared_ptr<IParagraph> m_paragraph;
};