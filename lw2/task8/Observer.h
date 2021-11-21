#pragma once
#include <boost/signals2/signal.hpp>

#include <map>
#include <vector>
#include <algorithm>
#include <functional>

namespace bs2 = boost::signals2;

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
	virtual void operator()(T const& data, SensorTypes sensorType) = 0;
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
	typedef typename bs2::signal<void(T const& data, SensorTypes sensorType)> Signal;
	typedef typename Signal::slot_type Observer;

	virtual ~IObservable() = default;
	virtual bs2::connection RegisterObserver(Observer& observer) = 0;
	virtual void NotifyObservers(SensorTypes sensorType) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	using Signal = typename IObservable<T>::Signal;
	using Observer = typename IObservable<T>::Observer;

	bs2::connection RegisterObserver(Observer& observer) override
	{
		return m_signal.connect( observer);
	}

	void NotifyObservers(SensorTypes sensorType) override
	{
		T data = GetChangedData();
		m_signal(data, sensorType);
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	Signal m_signal;
};
