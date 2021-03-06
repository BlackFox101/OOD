#include "WeatherData.h"
#include "Display.h"

int main()
{
	CWeatherData wd;

	//CDisplay display;
	//wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760);
	std::cout << "\n\n";
	wd.SetMeasurements(4, 0.8, 761);

	//wd.RemoveObserver(tempStatsDisplay);

	//wd.SetMeasurements(10, 0.8, 761);
	//wd.SetMeasurements(-10, 0.8, 761);

	return 0;
}