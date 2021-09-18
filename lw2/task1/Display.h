#pragma once
#include "WeatherData.h"

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class StatsDisplay : public IObserver<SWeatherInfo>
{
protected:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_countAcc = 0;
};


class CTempStatsDisplay : public StatsDisplay
{
private:
	virtual void Update(SWeatherInfo const& data)
	{
		if (m_min > data.temperature)
		{
			m_min = data.temperature;
		}
		if (m_max < data.temperature)
		{
			m_max = data.temperature;
		}
		m_acc += data.temperature;
		++m_countAcc;

		std::cout << "Max Temp " << m_max << std::endl;
		std::cout << "Min Temp " << m_min << std::endl;
		std::cout << "Average Temp " << (m_acc / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CHumStatsDisplay : public StatsDisplay
{
private:
	virtual void Update(SWeatherInfo const& data)
	{
		if (m_min > data.humidity)
		{
			m_min = data.humidity;
		}
		if (m_max < data.humidity)
		{
			m_max = data.humidity;
		}
		m_acc += data.humidity;
		++m_countAcc;

		std::cout << "Max Hum " << m_max << std::endl;
		std::cout << "Min Hum " << m_min << std::endl;
		std::cout << "Average Hum " << (m_acc / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CPressureStatsDisplay : public StatsDisplay
{
private:
	virtual void Update(SWeatherInfo const& data)
	{
		if (m_min > data.pressure)
		{
			m_min = data.pressure;
		}
		if (m_max < data.pressure)
		{
			m_max = data.pressure;
		}
		m_acc += data.pressure;
		++m_countAcc;

		std::cout << "Max Pressure " << m_max << std::endl;
		std::cout << "Min Pressure " << m_min << std::endl;
		std::cout << "Average Pressure " << (m_acc / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}
};
