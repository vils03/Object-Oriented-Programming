#include "Event.h"
#pragma warning(disable : 4996)


Event::Event(const Date& date, const Time& startTime) : _date(date), _startTime(startTime) {}

Event::Event(unsigned day, unsigned month, unsigned year,
	unsigned startTimeHours, unsigned startTimeMins, unsigned startTimeSecs) : _date(day, month, year),
	_startTime(startTimeHours, startTimeMins, startTimeSecs) {}

const Date& Event::getDate() const
{
	return _date;
}
const Time& Event::getStartTime() const
{
	return _startTime;
}

bool Event::lessThan(const Event& other)
{
	if(!_date.lessThan(other.getDate()))
		return false;
	else if(_startTime.compare(other.getStartTime()) > 1)
		return false;
	return true;
}

void Event::print() const
{
	_date.print();
	_startTime.print();
}

Event::Event() : Event(1, 1, 1, 0, 0, 0) {}