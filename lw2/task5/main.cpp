#include "WeatherData.h"
#include "Display.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	CStatsDisplay stats;
	wd.RegisterObserver(display, 1);
	wd.RegisterObserver(stats, 2);

	wd.SetMeasurements(3, 0.7, 760, 10, SWeatherInfo::WindDirection::East);
	wd.RemoveObserver(stats);
	wd.SetMeasurements(750, 50, 750, 30, SWeatherInfo::WindDirection::North);

	return 0;
}