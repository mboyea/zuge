#include "TimeTracker.h"

TimeTracker::TimeTracker() {

}

TimeTracker::~TimeTracker() {

}

void TimeTracker::OnUpdate() {
	clock_t lastTime = timeCurrent;
	timeCurrent = clock();

	timeDelta.clockTicks = lastTime - timeCurrent;
}