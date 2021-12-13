#include "stdafx.h"
#include "CImageSize.h"

CImageSize::CImageSize(int width, int height)
{
	if (!IsValidSize(width) || !IsValidSize(height))
	{
		throw std::invalid_argument("Invalid size. The size should be in the range from 1 to 100");
	}

	m_width = width;
	m_height = height;
}

int CImageSize::GetWidth() const
{
	return m_width;
}

int CImageSize::Getheight() const
{
	return m_height;
}

bool CImageSize::IsValidSize(int size)
{
	return !(size < IMAGE_SIZE_MIN || size > IMAGE_SIZE_MAX);
}
