#pragma once
#include <string>
#include <vector>
#include <map>
#include "WeatherData.h"

using namespace std;

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* ????? Update ?????? ?????????, ????? ?????????? ??????????? ??? ?????? ????????
		?????? CObservable ?? ????? ???????? ??? ?????, ?.?. ? ?????????? IObserver ??
		???????? ?????????
	*/
	void Update(SWeatherInfo const& data) override
	{
		cout << "Current Temp " << data.temperature << endl;
		cout << "Current Hum " << data.humidity << endl;
		cout << "Current Pressure " << data.pressure << endl;
		cout << "----------------" << endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data)
	{
		m_temperature.GetStats(data.temperature);
		m_humidity.GetStats(data.humidity);
		m_pressure.GetStats(data.pressure);
	}

private:
	class StatsItem
	{
	public:
		StatsItem(string name)
			: m_name(name)
		{
		}

		void GetStats(double parameter)
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

			std::cout << "Max " << m_name << " " << m_max << std::endl;
			std::cout << "Min " << m_name << " " << m_min << std::endl;
			std::cout << "Average " << m_name << " " << (m_acc / m_countAcc) << std::endl;
			std::cout << "----------------" << std::endl;
		}

	private:
		string m_name;
		double m_min = std::numeric_limits<double>::infinity();
		double m_max = -std::numeric_limits<double>::infinity();
		double m_acc = 0;
		unsigned m_countAcc = 0;
	};

	StatsItem m_temperature = "Temp"s;
	StatsItem m_humidity = "Hum"s;
	StatsItem m_pressure = "Pressure"s;
};