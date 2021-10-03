#include <iostream>
#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"

#include "../task4/WeatherData.h"
#include "../task4/Display.h"

class CustomWeatherData : public CWeatherData
{
public:
	typedef pair<ObserverType*, SensorTypes> Notification;
	typedef vector<Notification> NotificationType;

	CustomWeatherData(SensorTypes type)
		: CWeatherData(type)
	{}

	void NotifyObservers(SensorTypes sensorType) override
	{
		SWeatherInfo data = GetChangedData();
		for (auto it = m_observers.begin(); it != m_observers.end(); ++it)
		{
			vector<ObserverType*> observers = it->second;
			for (size_t i = 0; i < observers.size(); i++)
			{
				observers[i]->Update(data, sensorType);
				m_observers_received_notification.push_back({ observers[i], sensorType });
			}
		}
	}

	NotificationType GetObserversReceivedNotification()
	{
		return m_observers_received_notification;
	}

private:
	NotificationType m_observers_received_notification;
};

class CustomDisplay : public CDisplay
{
public:
	CustomDisplay(ostream& output)
		: m_output(output)
	{}
private:
	void Update(SWeatherInfo const& data, SensorTypes sensorType) override
	{
		string sensor = GetStringSensorType(sensorType);
		m_output << "Current " << sensor << " Temp " << data.temperature << endl;
		m_output << "Current " << sensor << " Hum " << data.humidity << endl;
		m_output << "Current " << sensor << " Pressure " << data.pressure << endl;
		m_output << "----------------" << endl;
	}

	ostream& m_output;
};

class CustomStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CustomStatsDisplay(ostream& output)
		: m_output(output)
	{}
private:
	void Update(SWeatherInfo const& data, SensorTypes sensorType)
	{
		if (sensorType == SensorTypes::In)
		{
			m_stats_in.temperature.GetStats(data.temperature, SensorTypes::In, m_output);
			m_stats_in.humidity.GetStats(data.humidity, SensorTypes::In, m_output);
			m_stats_in.pressure.GetStats(data.pressure, SensorTypes::In, m_output);
			return;
		}

		m_stats_out.temperature.GetStats(data.temperature, SensorTypes::Out, m_output);
		m_stats_out.humidity.GetStats(data.humidity, SensorTypes::Out, m_output);
		m_stats_out.pressure.GetStats(data.pressure, SensorTypes::Out, m_output);
	}

	// TODO: не должен знать in или out
	class StatsItem
	{
	public:
		StatsItem(string name)
			: m_name(name)
		{}

		void GetStats(double parameter, SensorTypes sensorType, ostream& output)
		{
			if (m_min > parameter)
			{
				m_min = parameter;
			}
			if (m_max < parameter)
			{
				m_max = parameter;
			}
			m_acc += parameter;
			++m_countAcc;

			string sensor = GetStringSensorType(sensorType);
			output << "Max " + sensor << " " << m_name << " " << m_max << endl;
			output << "Min " + sensor << " " << m_name << " " << m_min << endl;
			output << "Average " + sensor << " " << m_name << " " << (m_acc / m_countAcc) << endl;
			output << "----------------" << endl;
		}

	private:
		string m_name;
		double m_min = std::numeric_limits<double>::infinity();
		double m_max = -std::numeric_limits<double>::infinity();
		double m_acc = 0;
		unsigned m_countAcc = 0;
	};

	struct Subject
	{
		StatsItem temperature;
		StatsItem humidity;
		StatsItem pressure;
	};

	Subject m_stats_in = {
		StatsItem("Temp"s),
		StatsItem("Hum"s),
		StatsItem("Pressure"s),
	};
	Subject m_stats_out = {
		StatsItem("Temp"s),
		StatsItem("Hum"s),
		StatsItem("Pressure"s),
	};

	ostream& m_output;
};

TEST_CASE("Monitoring of several subjects")
{
	WHEN("In or Out")
	{
		THEN("1")
		{
			CustomWeatherData wdIn(SensorTypes::In);
			CustomWeatherData wdOut(SensorTypes::Out);

			CDisplay display;
			CStatsDisplay stats;

			wdIn.RegisterObserver(stats, 1);
			wdOut.RegisterObserver(stats, 2);

			wdIn.SetMeasurements(3, 0.7, 760);
			wdOut.SetMeasurements(4, 1, 780);
			auto InObservers = wdIn.GetObserversReceivedNotification();
			auto OutObservers = wdOut.GetObserversReceivedNotification();

			REQUIRE(InObservers[0].second == SensorTypes::In);
			REQUIRE(OutObservers[0].second == SensorTypes::Out);
		}
	}
	WHEN("Display Texts")
	{
		THEN("In text")
		{

			THEN("Out Display")
			{
				std::ostringstream output;
				CustomWeatherData wdIn(SensorTypes::In);
				CustomDisplay display(output);

				wdIn.RegisterObserver(display, 1);

				wdIn.SetMeasurements(3, 0.7, 760);
				auto observers = wdIn.GetObserversReceivedNotification();
				REQUIRE(observers[0].second == SensorTypes::In);
				CHECK(output.str() == "Current In Temp 3\n"
									  "Current In Hum 0.7\n"
									  "Current In Pressure 760\n"
									  "----------------\n");
			}
			THEN("In Display")
			{
				std::ostringstream output;
				CustomWeatherData wdOut(SensorTypes::Out);
				CustomDisplay display(output);

				wdOut.RegisterObserver(display, 1);

				wdOut.SetMeasurements(3, 0.7, 760);
				auto observers = wdOut.GetObserversReceivedNotification();
				REQUIRE(observers[0].second == SensorTypes::Out);
				CHECK(output.str() == "Current Out Temp 3\n"
					"Current Out Hum 0.7\n"
					"Current Out Pressure 760\n"
					"----------------\n");
			}
		}
	}
	WHEN("Stats tests")
	{
		THEN("In texts")
		{
			std::ostringstream output;
			CustomWeatherData wdIn(SensorTypes::In);

			CustomStatsDisplay stats(output);
			wdIn.RegisterObserver(stats, 1);

			wdIn.SetMeasurements(3, 0.7, 760);
			REQUIRE(output.str() == "Max In Temp 3\n"
									"Min In Temp 3\n"
									"Average In Temp 3\n"
									"----------------\n"
									"Max In Hum 0.7\n"
									"Min In Hum 0.7\n"
									"Average In Hum 0.7\n"
									"----------------\n"
									"Max In Pressure 760\n"
									"Min In Pressure 760\n"
									"Average In Pressure 760\n"
									"----------------\n");

		}
		THEN("Out texts")
		{
			std::ostringstream output;
			CustomWeatherData wdOut(SensorTypes::Out);

			CustomStatsDisplay stats(output);
			wdOut.RegisterObserver(stats, 1);

			wdOut.SetMeasurements(3, 0.7, 760);
			REQUIRE(output.str() == "Max Out Temp 3\n"
									"Min Out Temp 3\n"
									"Average Out Temp 3\n"
									"----------------\n"
									"Max Out Hum 0.7\n"
									"Min Out Hum 0.7\n"
									"Average Out Hum 0.7\n"
									"----------------\n"
									"Max Out Pressure 760\n"
									"Min Out Pressure 760\n"
									"Average Out Pressure 760\n"
									"----------------\n");
		}
		THEN("Different stats Out and In")
		{
			std::ostringstream output;
			CustomWeatherData wdIn(SensorTypes::In);
			CustomWeatherData wdOut(SensorTypes::Out);

			CustomStatsDisplay stats(output);
			wdIn.RegisterObserver(stats, 1);
			wdOut.RegisterObserver(stats, 1);

			wdIn.SetMeasurements(3, 0.7, 760);
			REQUIRE(output.str() == "Max In Temp 3\n"
									"Min In Temp 3\n"
									"Average In Temp 3\n"
									"----------------\n"
									"Max In Hum 0.7\n"
									"Min In Hum 0.7\n"
									"Average In Hum 0.7\n"
									"----------------\n"
									"Max In Pressure 760\n"
									"Min In Pressure 760\n"
									"Average In Pressure 760\n"
									"----------------\n");

			output.str("");
			wdOut.SetMeasurements(5, 1.5, 730);
			REQUIRE(output.str() == "Max Out Temp 5\n"
									"Min Out Temp 5\n"
									"Average Out Temp 5\n"
									"----------------\n"
									"Max Out Hum 1.5\n"
									"Min Out Hum 1.5\n"
									"Average Out Hum 1.5\n"
									"----------------\n"
									"Max Out Pressure 730\n"
									"Min Out Pressure 730\n"
									"Average Out Pressure 730\n"
									"----------------\n");
		}
	}
}