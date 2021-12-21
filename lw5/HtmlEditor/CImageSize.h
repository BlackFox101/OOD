#pragma once

class CImageSize
{
public:
	static const int IMAGE_SIZE_MAX = 10000;
	static const int IMAGE_SIZE_MIN = 1;

	CImageSize(int width, int height);
	CImageSize();
	int GetWidth() const;
	int GetHeight() const;
private:
	int m_width = 0, m_height = 0;

	static bool IsValidSize(int width);
};

