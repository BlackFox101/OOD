#pragma once
#include <string>
#include <vector>
#include "Observer.h"
#include "WeatherData.h"

using namespace std;

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

	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
		������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
		�������� ���������
	*/
	void Update(SWeatherInfo const& data, SensorTypes sensorType) override
	{
		string sensor = GetStringSensorType(sensorType);
		cout << "Current " << sensor << " Temp " << data.temperature << endl;
		cout << "Current " << sensor << " Hum " << data.humidity << endl;
		cout << "Current " << sensor << " Pressure " << data.pressure << endl;
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
	}

	// TODO: �� ������ ����� in ��� out
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
};