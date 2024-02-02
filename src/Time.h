#ifndef TIME_H
#define TIME_H
#pragma once

#include <ctime>

class Time {
public:
	Time();
	Time(time_t newClockTicks);

	clock_t clockTicks;

	double GetMilisecs();
	double GetSecs();
	double GetMins();
	double GetHours();

};

#endif // TIME_H