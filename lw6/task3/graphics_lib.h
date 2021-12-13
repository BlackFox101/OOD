#pragma once
#include <iostream>
#include <iomanip>
#include <cstdint>

using namespace std;

// ������������ ���� ����������� ���������� (���������� ��� ���������)
namespace graphics_lib
{
    // ����� ��� ���������
    class ICanvas
    {
    public:
        // ��������� ����� � ������� 0xRRGGBB
        virtual void SetColor(uint32_t rgbColor) = 0;
        // ������ "����" � ����� x, y
        virtual void MoveTo(int x, int y) = 0;
        // ������ ����� � ������� �������, ���������� ���� � ����� x,y
        virtual void LineTo(int x, int y) = 0;
        virtual ~ICanvas() = default;
    };

    // ���������� ������ ��� ���������
    class CCanvas : public ICanvas
    {
    public:
        void SetColor(uint32_t rgbColor) override
        {
            cout << '#' << setfill('0') << uppercase << setw(6) << hex << rgbColor << '\n';
        }
        void MoveTo(int x, int y) override
        {
            cout << "MoveTo (" << x << ", " << y << ")" << endl;
        }
        void LineTo(int x, int y) override
        {
            cout << "LineTo (" << x << ", " << y << ")" << endl;
        }
    };
}
