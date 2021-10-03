#include <iostream>
#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"

#include "../task3/WeatherData.h"
#include "../task3/Display.h"


class CustomObservable : public CWeatherData
{
public:
	void NotifyObservers() override
	{
		SWeatherInfo data = GetChangedData();
		for (auto it = m_observers.begin(); it != m_observers.end(); ++it)
		{
			vector<ObserverType*> observers = it->second;
			for (size_t i = 0; i < observers.size(); i++)
			{
				observers[i]->Update(data);
				m_observers_received_notification.push_back(observers[i]);
			}
		}
	}

	vector<ObserverType*> GetObserversReceivedNotification()
	{
		return m_observers_received_notification;
	}

private:
	vector<ObserverType*> m_observers_received_notification;
};

TEST_CASE("Checking the priority of the observers")
{
	WHEN("Different priority")
	{
		THEN("1")
		{
			CustomObservable wd;
			CDisplay display;
			CStatsDisplay stats;

			wd.RegisterObserver(display, 1);
			wd.RegisterObserver(stats, 3);
			//wd.RemoveObserver(stats);

			wd.SetMeasurements(3, 0.7, 760);

			auto observers = wd.GetObserversReceivedNotification();
			REQUIRE(observers.size() == 2);
			CHECK(observers[0] == &display);
			CHECK(observers[1] == &stats);
		}
		THEN("2")
		{
			CustomObservable wd;
			CDisplay display;
			CStatsDisplay stats;

			wd.RegisterObserver(display, 3);
			wd.RegisterObserver(stats, 1);

			wd.SetMeasurements(3, 0.7, 760);

			auto observers = wd.GetObserversReceivedNotification();
			REQUIRE(observers.size() == 2);
			CHECK(observers[0] == &stats);
			CHECK(observers[1] == &display);
		}
		THEN("Remove observer")
		{
			CustomObservable wd;
			CDisplay display;
			CStatsDisplay stats;

			wd.RegisterObserver(display, 3);
			wd.RegisterObserver(stats, 1);
			wd.RemoveObserver(stats);

			wd.SetMeasurements(3, 0.7, 760);
			auto observers = wd.GetObserversReceivedNotification();
			REQUIRE(observers.size() == 1);
			CHECK(observers[0] == &display);
		}
	}
}