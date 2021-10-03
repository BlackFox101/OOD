#include "WeatherData.h"
#include "Display.h"

int main()
{
	CInWeatherData wdIn;
	COutWeatherData wdOut;

	CDisplay display;
	CStatsDisplay stats;

	//wd.RegisterObserver(display, 1);
	//wd.RegisterObserver(stats, 2);
	wdOut.RegisterObserver(stats, 1);
	wdIn.RegisterObserver(stats, 1);

	wdOut.SetMeasurements(3, 0.7, 760, 10, SWeatherInfo::WindDirection::East);
	wdIn.SetMeasurements(750, 50, 750);
}
