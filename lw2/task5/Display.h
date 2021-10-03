#pragma once
#include <string>
#include <vector>
#include <cmath>
#include "Observer.h"
#include "WeatherData.h"

using namespace std;

string GetWindDirectionName(SWeatherInfo::WindDirection windDirection)
{
	switch (windDirection)
	{
	case SWeatherInfo::WindDirection::East:
		return "East";
	case SWeatherInfo::WindDirection::South:
		return "South";
	case SWeatherInfo::WindDirection::West:
		return "West";
	default:
		return "North";
	}
	return "";
}

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		cout << "Current Temp: " << data.temperature << endl;
		cout << "Current Hum: " << data.humidity << endl;
		cout << "Current Pressure: " << data.pressure << endl;
		cout << "Current Wind Speed: " << data.windSpeed << endl;
		cout << "Current Wind Direction: " << GetWindDirectionName(data.windDirection) << endl;
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
		m_windSpeed.GetStats(data.windSpeed);
		m_windDirection.GetStats(data.windDirection, data.windSpeed);
	}

private:
	class StatsItem
	{
	public:
		StatsItem(string name)
			: m_name(name)
		{}

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

			std::cout << "Max " << m_name << ": " << m_max << std::endl;
			std::cout << "Min " << m_name << ": " << m_min << std::endl;
			std::cout << "Average " << m_name << ": " << (m_acc / m_countAcc) << std::endl;
			std::cout << "----------------" << std::endl;
		}

	private:
		string m_name;
		double m_min = std::numeric_limits<double>::infinity();
		double m_max = -std::numeric_limits<double>::infinity();
		double m_acc = 0;
		unsigned m_countAcc = 0;
	};

	class WindStats
	{
	public:
		WindStats(string name)
			: m_name(name)
		{}

		void GetStats(SWeatherInfo::WindDirection windDirection, double windSpeed)
		{
			string direction = GetNewWindDirection(windDirection, windSpeed);

			cout << "Average " << m_name << ": " << direction << std::endl;
			cout << "----------------" << std::endl;
		}

	private:
		struct Vector
		{
			double wSin;
			double wCos;
		};

		string m_name;
		Vector m_accWind = {0, 0};

		string GetNewWindDirection(SWeatherInfo::WindDirection windDirection, double windSpeed)
		{
			double corner = GetNewCorner(windDirection, windSpeed);

			return GetWindDirectionName(GetDirectionByCorner(corner));
		}

		double GetNewCorner(SWeatherInfo::WindDirection windDirection, double windSpeed)
		{
			double corner = (double)windDirection * 3.14 / 180;
			m_accWind.wSin += m_accWind.wSin + sin(corner);
			m_accWind.wCos += m_accWind.wCos + cos(corner);
			corner = atan2(m_accWind.wCos, m_accWind.wCos) / 3.14 * 180.0;

			if (corner < 0)
			{
				corner += 360;
			}

			return corner;
		}

		static SWeatherInfo::WindDirection GetDirectionByCorner(double corner)
		{
			if (corner > 45  && corner <= 135)
			{
				return SWeatherInfo::WindDirection::East;
			}
			if (corner > 135 && corner <= 225)
			{
				return SWeatherInfo::WindDirection::South;
			}
			if (corner > 225 && corner <= 315)
			{
				return SWeatherInfo::WindDirection::West;
			}

			return SWeatherInfo::WindDirection::North;
		}
	};

	StatsItem m_temperature = "Temp"s;
	StatsItem m_humidity = "Hum"s;
	StatsItem m_pressure = "Pressure"s;
	StatsItem m_windSpeed = "Wind Speed"s;
	WindStats m_windDirection = "Wind Direction"s;
};