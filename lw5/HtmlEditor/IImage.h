#pragma once
#include "stdafx.h"
#include "CImageSize.h"

typedef std::filesystem::path Path;

/* Изображение */
class IImage
{
public:
	// Возвращает путь относительно каталога документа
	virtual Path GetPath() const = 0;

	// Ширина изображения в пикселях
	virtual int GetWidth() const = 0;
	// Высота изображения в пикселях
	virtual int GetHeight() const = 0;

	// Изменяет размер изображения
	virtual void Resize(CImageSize size) = 0;

	virtual ~IImage() = default;
};