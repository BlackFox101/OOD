#include "stdafx.h"
#include "Image.h"
#include "CImageSize.h"
#include "CResizeImageCommand.h"

using namespace std;

Image::Image(IHistory& history, const Path& path, int width, int height)
    : m_history(history)
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

    m_size = { width, height };
    m_path = newPath;
}

Image::~Image()
{
    filesystem::remove(m_path);
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
    return m_size.GetHeight();
}

void Image::Resize(CImageSize size)
{
    m_history.AddAndExecuteCommand(make_unique<CResizeImageCommand>(m_size, size));
}

Path Image::SaveFileToDirectory(const Path& path)
{
    Path newPath(IMAGE_DIRECTORY_PATH + GenerateFileName() + path.extension().string());

    filesystem::create_directory(IMAGE_DIRECTORY_PATH);
    filesystem::copy_file(path, newPath, filesystem::copy_options::overwrite_existing);
    return newPath;
}

string Image::GenerateFileName()
{
    string chars = "1234567890AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
    string name;
    for (int i = 0; i < 10; i++)
    {
        name += chars[rand() % chars.size()];
    }
    return name;
}

void Image::CheckImageSizeInPixels(const Path& path)
{
    // Проверка размеры картинки в пикселях
    // Рзаме
}