#include <Windows.h>
#include "ChartDrawerView.h"
#include "HarmonicsStorage.h"
#include "ChartDrawerController.h"

using namespace lw9;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	typedef std::function<void(std::shared_ptr<HarmonicInterface>)> AddNewHarmonicCallback;
	typedef std::function<void(size_t)> DeleteHarmonicCallback;

	std::shared_ptr<HarmonicsStorageInterface> model = std::make_shared<HarmonicsStorage>();
	std::shared_ptr<ChartDrawerControllerInterface> controller = std::make_shared<ChartDrawerController>(model);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew ChartDrawerView(model, controller));
	return 0;
}