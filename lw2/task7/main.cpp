#include "WeatherData.h"
#include "Display.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	CStatsDisplay stats;

	wd.RegisterObserver(display, WeatherEvent::Temperature);
	wd.RegisterObserver(stats, WeatherEvent::WindSpeed);

	wd.SetMeasurements(3, 0.7, 760, 10, SWeatherInfo::WindDirection::East);
	//wd.RemoveObserver(stats);
	wd.SetMeasurements(4, 50, 750, 30, SWeatherInfo::WindDirection::North);
}
