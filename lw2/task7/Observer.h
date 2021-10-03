#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template <typename T, typename E>
class IObserver
{
public:
	virtual void Update(T const& data, E event) = 0;
	virtual ~IObserver() = default;
};

template <typename T, typename E>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T, E>& observer, E event) = 0;
	virtual void NotifyObservers(vector<E> events) = 0;
	virtual void RemoveObserver(IObserver<T, E>& observer) = 0;
};

template <class T, typename E>
class CObservable : public IObservable<T, E>
{
public:
	typedef IObserver<T, E> ObserverType;

	void RegisterObserver(ObserverType& observer, E event) override
	{
		m_events[event].push_back(&observer);
		m_observerEvents[&observer] = event;
	}

	void NotifyObservers(vector<E> events) override
	{
		T data = GetChangedData();
		for (size_t i = 0; i < events.size(); i++)
		{
			E event = events[i];
			auto observers = m_events[event];

			for (size_t i = 0; i < observers.size(); i++)
			{
				observers[i]->Update(data, event);
			}
		}

		/*for (auto it = m_events.begin(); it != m_events.end(); ++it)
		{
			vector<ObserverType*> observers = it->second;
			for (size_t i = 0; i < observers.size(); i++)
			{
				observers[i]->Update(data, it->first);
			}
		}*/
	}

	void RemoveObserver(ObserverType& observer) override
	{
		E observerEvent = m_observerEvents[&observer];
		auto it = find(m_events[observerEvent].begin(), m_events[observerEvent].end(), &observer);
		m_events[observerEvent].erase(it);
		m_observerEvents.erase(&observer);
	}

protected:
	virtual T GetChangedData() const = 0;

private:

	map<E, vector<ObserverType*>> m_events;
	map<ObserverType*, E> m_observerEvents;
};
