#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct SWeatherInfo
{
	enum class WindDirection
	{
		North = 0,
		East = 90,
		South = 180,
		West = 270
	};

	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	WindDirection windDirection = WindDirection::North;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	double GetTemperature() const
	{
		return m_temperature;
	}
	double GetHumidity() const
	{
		return m_humidity;
	}
	double GetPressure() const
	{
		return m_pressure;
	}
	double GetWindSpeed() const
	{
		return m_windSpeed;
	}
	SWeatherInfo::WindDirection GetWindDirection() const
	{
		return m_windDirection;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, SWeatherInfo::WindDirection windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windSpeed = windSpeed;
		m_windDirection = windDirection;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = m_temperature;
		info.humidity = m_humidity;
		info.pressure = m_pressure;
		info.windSpeed = m_windSpeed;
		info.windDirection = m_windDirection;
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;
	double m_windSpeed = 0;
	SWeatherInfo::WindDirection m_windDirection = SWeatherInfo::WindDirection::North;
};
