#pragma once

class CImageSize
{
public:
	static const int IMAGE_SIZE_MAX = 100;
	static const int IMAGE_SIZE_MIN = 1;

	CImageSize(int width, int height);
	int GetWidth() const;
	int Getheight() const;
private:
	int m_width, m_height;

	static bool IsValidSize(int width);
};

