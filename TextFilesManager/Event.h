#pragma once
#include "Time.h"
#include "Date.h"
class Event
{
	Date _date;
	Time _startTime;

public:
	Event();
	Event(const Date& date, const Time& startTime);

	Event(unsigned day, unsigned month, unsigned year,
		unsigned startTimeHours, unsigned startTimeMins, unsigned startTimeSecs);

	const Date& getDate() const;
	const Time& getStartTime() const;

	void print() const;

};