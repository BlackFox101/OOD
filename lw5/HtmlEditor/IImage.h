#pragma once
#include "stdafx.h"
#include "CImageSize.h"

typedef std::filesystem::path Path;

/* ����������� */
class IImage
{
public:
	// ���������� ���� ������������ �������� ���������
	virtual Path GetPath() const = 0;

	// ������ ����������� � ��������
	virtual int GetWidth() const = 0;
	// ������ ����������� � ��������
	virtual int GetHeight() const = 0;

	// �������� ������ �����������
	virtual void Resize(CImageSize size) = 0;

	virtual ~IImage() = default;
};