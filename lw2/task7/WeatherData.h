#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

enum class WeatherEvent
{
	Temperature,
	Humidity,
	Pressure,
	WindSpeed,
	WindDirection
};

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

class CWeatherData : public CObservable<SWeatherInfo, WeatherEvent>
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

	void MeasurementsChanged(vector<WeatherEvent> modifiedEvents)
	{
		
		NotifyObservers(modifiedEvents);
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, SWeatherInfo::WindDirection windDirection)
	{
		vector<WeatherEvent> modifiedEvents;
		if (m_humidity != humidity)
		{
			m_humidity = humidity;
			modifiedEvents.push_back(WeatherEvent::Humidity);
		}
		if (m_temperature != temp)
		{
			m_temperature = temp;
			modifiedEvents.push_back(WeatherEvent::Temperature);
		}
		if (m_pressure != pressure)
		{
			m_pressure = pressure;
			modifiedEvents.push_back(WeatherEvent::Pressure);
		}
		if (m_windSpeed != windSpeed)
		{
			m_windSpeed = windSpeed;
			modifiedEvents.push_back(WeatherEvent::WindSpeed);
		}

		if (m_windDirection != windDirection)
		{
			m_windDirection = windDirection;
			modifiedEvents.push_back(WeatherEvent::WindDirection);
		}

		MeasurementsChanged(modifiedEvents);
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

	vector<WeatherEvent> GetModifiedEvents()
	{

	}

	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;
	double m_windSpeed = 0;
	SWeatherInfo::WindDirection m_windDirection = SWeatherInfo::WindDirection::North;
};
