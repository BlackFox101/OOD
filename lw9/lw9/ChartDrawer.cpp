#include "ChartDrawer.h"
#include <Windows.h>

using namespace lw9;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew ChartDrawer);
	return 0;
}