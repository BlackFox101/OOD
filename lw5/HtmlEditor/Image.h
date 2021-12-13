#pragma once
#include "stdafx.h"
#include "IImage.h"
#include "CHistory.h"
#include "CImageSize.h"

class Image : public IImage
{
public:
	Image(CHistory& history, const Path& path, CImageSize& size);
	Path GetPath() const override;
	int GetWidth() const override;
	int GetHeight() const override;
	void Resize(CImageSize size) override;

private:
	CHistory& m_history;
	Path m_path;
	CImageSize& m_size;

	const std::set<std::string> SUPPORTED_EXTINSION{".jpg", ".jpeg", ".png", ".svg"};
	static void CheckImageSizeInPixels(const Path& path);
	static Path SaveFileToDirectory(const Path& path);
	static std::string GenerateFileName();
};

