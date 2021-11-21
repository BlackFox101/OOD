#pragma once
#include <map>
#include <vector>

#include "Observer.h"

enum class SensorTypes
{
	In,
	Out
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, Priority priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
	virtual SensorTypes getType() = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	CObservable(SensorTypes sensorType)
		: m_type(sensorType)
	{}

	typedef IObserver<T> ObserverType;
	typedef pair<ObserverType*, Priority> Observer;

	SensorTypes getType() override
	{
		return m_type;
	}

	void RegisterObserver(ObserverType& observer, Priority priority) override
	{
		m_observers[priority].push_back(&observer);
		m_observerPriority[&observer] = priority;
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		for (auto it = m_observers.begin(); it != m_observers.end(); ++it)
		{
			vector<ObserverType*> observers = it->second;
			for (size_t i = 0; i < observers.size(); i++)
			{
				observers[i]->Update(data, *this);
			}
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		Priority observerPriority = m_observerPriority[&observer];
		auto it = find(m_observers[observerPriority].begin(), m_observers[observerPriority].end(), &observer);
		m_observers[observerPriority].erase(it);
		m_observerPriority.erase(&observer);
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	map<Priority, vector<ObserverType*>> m_observers;
	map<ObserverType*, Priority> m_observerPriority;
	SensorTypes m_type;

	friend class CustomWeatherData;
};