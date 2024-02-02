#include "Time.h"

Time::Time() {
	clockTicks = clock();
}

Time::Time(time_t newClockTicks) {
	clockTicks = newClockTicks;
}

double Time::GetMilisecs() {
	return clockTicks / ((double)CLOCKS_PER_SEC / 1000.0);
}

double Time::GetSecs() {
	return clockTicks / (double)CLOCKS_PER_SEC;
}

double Time::GetMins() {
	return clockTicks / (60 * (double)CLOCKS_PER_SEC);
}

double Time::GetHours() {
	return clockTicks / (60 * 60 * (double)CLOCKS_PER_SEC);
}