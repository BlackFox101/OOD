#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include <functional>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/

using namespace std;

typedef int Priority;

enum class SensorTypes
{
	In,
	Out,
};

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, SensorTypes sensorType) = 0;
	virtual ~IObserver() = default;
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
	virtual void NotifyObservers(SensorTypes sensorType) = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;
	typedef pair<ObserverType*, Priority> Observer;

	void RegisterObserver(ObserverType& observer, Priority priority) override
	{
		m_observers[priority].push_back(&observer);
		m_observerPriority[&observer] = priority;
	}

	void NotifyObservers(SensorTypes sensorType) override
	{
		T data = GetChangedData();
		for (auto it = m_observers.begin(); it != m_observers.end(); ++it)
		{
			vector<ObserverType*> observers = it->second;
			for (size_t i = 0; i < observers.size(); i++)
			{
				observers[i]->Update(data, sensorType);
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

	friend class CustomWeatherData;
};
