#pragma once
#include <string>
#include <vector>
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

string GetStringSensorType(SensorTypes sensorType)
{
	if (sensorType == SensorTypes::In)
	{
		return "In";
	}
	return "Out";
}

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data, SensorTypes sensorType) override
	{
		string sensor = GetStringSensorType(sensorType);
		cout << "Current " << sensor << " Temp " << data.temperature << endl;
		cout << "Current " << sensor << " Hum " << data.humidity << endl;
		cout << "Current " << sensor << " Pressure " << data.pressure << endl;
		if (sensorType == SensorTypes::Out)
		{
			cout << "Current " << sensor << " Wind Speed: " << data.windSpeed << endl;
			cout << "Current " << sensor << " Wind Direction: " << GetWindDirectionName(data.windDirection) << endl;
		}
		cout << "----------------" << endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data, SensorTypes sensorType)
	{
		if (sensorType == SensorTypes::In)
		{
			m_stats_in.temperature.GetStats(data.temperature, SensorTypes::In);
			m_stats_in.humidity.GetStats(data.humidity, SensorTypes::In);
			m_stats_in.pressure.GetStats(data.pressure, SensorTypes::In);
			return;
		}

		m_stats_out.temperature.GetStats(data.temperature, SensorTypes::Out);
		m_stats_out.humidity.GetStats(data.humidity, SensorTypes::Out);
		m_stats_out.pressure.GetStats(data.pressure, SensorTypes::Out);
		m_stats_out.windSpeed.GetStats(data.windSpeed, SensorTypes::Out);
		m_stats_out.windDirection.GetStats(data.windDirection, data.windSpeed, SensorTypes::Out);
	}

	class StatsItem
	{
	public:
		StatsItem(string name)
			: m_name(name)
		{}

		void GetStats(double parameter, SensorTypes sensorType)
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
			cout << "Max " + sensor << " " << m_name << " " << m_max << endl;
			cout << "Min " + sensor << " " << m_name << " " << m_min << endl;
			cout << "Average " + sensor << " " << m_name << " " << (m_acc / m_countAcc) << endl;
			cout << "----------------" << endl;
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
		{
		}

		void GetStats(SWeatherInfo::WindDirection windDirection, double windSpeed, SensorTypes sensorType)
		{
			string sensor = GetStringSensorType(sensorType);
			string direction = GetNewWindDirection(windDirection, windSpeed);

			cout << "Average " << sensor << m_name << ": " << direction << std::endl;
			cout << "----------------" << std::endl;
		}

	private:
		struct Vector
		{
			double wSin;
			double wCos;
		};

		string m_name;
		Vector m_accWind = { 0, 0 };

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
			if (corner > 45 && corner <= 135)
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

	struct InSubject
	{
		StatsItem temperature;
		StatsItem humidity;
		StatsItem pressure;
	};
	struct OutSubject
	{
		StatsItem temperature;
		StatsItem humidity;
		StatsItem pressure;
		StatsItem windSpeed;
		WindStats windDirection;
	};

	InSubject m_stats_in = {
		StatsItem("Temp"s),
		StatsItem("Hum"s),
		StatsItem("Pressure"s),
	};
	OutSubject m_stats_out = {
		StatsItem("Temp"s),
		StatsItem("Hum"s),
		StatsItem("Pressure"s),
		StatsItem("Wind Speed"s),
		WindStats("Wind Directions"),
	};
};