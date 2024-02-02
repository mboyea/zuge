#ifndef TIMETRACKER
#define TIMETRACKER
#pragma once

#include <ctime>
#include "Time.h"

class TimeTracker {
private:
	clock_t timeStart = clock();
	clock_t timeCurrent = clock();

public:
	Time timeDelta;

	TimeTracker();
	~TimeTracker();

	void OnUpdate();
	
	clock_t GetTimeStart() { return timeStart; }
	clock_t GetTimeCurrent() { return timeCurrent; }
};

#endif // TIMETRACKER