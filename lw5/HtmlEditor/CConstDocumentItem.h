#pragma once
#include "Image.h"
#include "Paragraph.h"

/* ������������ ������� ��������� */
class CConstDocumentItem
{
public:
	CConstDocumentItem(std::shared_ptr<IImage> image);
	CConstDocumentItem(std::shared_ptr<IParagraph> paragraph);

	// ���������� ��������� �� ����������� �����������, ���� nullptr, ���� ������� �� �������� ������������
	std::shared_ptr<const IImage> GetImage() const;
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<const IParagraph> GetParagraph() const;
	virtual ~CConstDocumentItem() = default;

protected:
	std::shared_ptr<IImage> m_image;
	std::shared_ptr<IParagraph> m_paragraph;
};