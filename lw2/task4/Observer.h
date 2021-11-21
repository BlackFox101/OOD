#pragma once
#include "Observable.h"
/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/

using namespace std;

typedef int Priority;

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, CObservable<SWeatherInfo>& observable) = 0;
	virtual ~IObserver() = default;
};