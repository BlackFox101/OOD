#include "ChartDrawerView.h"
#include <Windows.h>

using namespace lw9;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew ChartDrawerView);
	return 0;
}