#pragma once
#include "stdafx.h"
#include "IImage.h"
#include "CHistory.h"
#include "CImageSize.h"

typedef std::filesystem::path Path;

class Image : public IImage
{
public:
	Image(CHistory& history, const Path& path, int width, int height);
	Path GetPath() const override;
	int GetWidth() const override;
	int GetHeight() const override;
	void Resize(CImageSize size) override;

private:
	CHistory& m_history;
	Path m_path;
	CImageSize m_size;
	const std::string IMAGE_DIRECTORY_PATH = "./images/";

	const std::set<std::string> SUPPORTED_EXTINSION{".jpg", ".jpeg", ".png", ".svg"};
	static void CheckImageSizeInPixels(const Path& path);
	Path SaveFileToDirectory(const Path& path);
	static std::string GenerateFileName();
};

