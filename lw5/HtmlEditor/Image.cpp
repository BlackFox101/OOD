#include "stdafx.h"
#include "Image.h"
#include "CImageSize.h"
#include "CResizeImageCommand.h"

using namespace std;

Image::Image(CHistory& history, const Path& path, CImageSize& size)
    : m_history(history)
    , m_size(size)
{
    if (!filesystem::exists(path))
    {
        throw invalid_argument("There is no file in the specified path");
    }

    string extension = path.extension().string();
    if (SUPPORTED_EXTINSION.find(extension) == SUPPORTED_EXTINSION.end())
    {
        throw invalid_argument("Unsupported image extension");
    }

    CheckImageSizeInPixels(path);
    Path newPath = SaveFileToDirectory(path);

    m_path = newPath;
}

Path Image::GetPath() const
{
    return m_path;
}

int Image::GetWidth() const
{
    return m_size.GetWidth();
}

int Image::GetHeight() const
{
    return m_size.Getheight();
}

void Image::Resize(CImageSize size)
{
    m_history.AddAndExecuteCommand(make_unique<CResizeImageCommand>(m_size, size));
}

Path Image::SaveFileToDirectory(const Path& path)
{
    // TODO: сохранение файла в свою директорию
    return path;
}

string Image::GenerateFileName()
{
    // TODO: создание имени файла
    return "";
}

void Image::CheckImageSizeInPixels(const Path& path)
{
    // Проверка размеры картинки в пикселях
}