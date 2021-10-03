#include "WeatherData.h"
#include "Display.h"

int main()
{
	// TODO: 2 объекта WeatherData
	CWeatherData wdIn(SensorTypes::In);
	CWeatherData wdOut(SensorTypes::In);
	
	CDisplay display;
	CStatsDisplay stats;
	//wdIn.RegisterObserver(display, 1);
	//wdOut.RegisterObserver(display, 1);

	wdIn.RegisterObserver(stats, 1);
	wdOut.RegisterObserver(stats, 1);

	wdIn.SetMeasurements(3, 0.7, 760);
	wdOut.SetMeasurements(6, 1.4, 770);

	/*CStatsDisplay statsDisplay;

	wd.RegisterObserver(display, 1);
	wd.RegisterObserver(statsDisplay, 2);

	*/

	return 0;
}