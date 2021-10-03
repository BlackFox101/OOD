#include <iostream>
#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"

#include "../task2/WeatherData.h"
#include "../task2/Display.h"

TEST_CASE("Removing yourself from the list of observers")
{
	CWeatherData wd;
	CDisplay display(wd);
	wd.RegisterObserver(display);
	REQUIRE_NOTHROW(wd.SetMeasurements(3, 0.7, 760));
	REQUIRE_NOTHROW(wd.SetMeasurements(3, 0.7, 760));
}