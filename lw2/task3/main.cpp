#include "WeatherData.h"
#include "Display.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	CStatsDisplay stats;
	wd.RegisterObserver(display, 2);
	wd.RegisterObserver(stats, 1);

	wd.SetMeasurements(3, 0.7, 760);
	wd.RemoveObserver(display);
	wd.SetMeasurements(3, 0.7, 790);

	return 0;
}