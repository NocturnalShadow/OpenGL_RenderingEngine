
#include "Timer.h"

void Timer::run()
{
	if (!isRunning) {
		if (isPaused) {
			isPaused = false;
		} else {
			beg = steady_clock::now();
		}
		isRunning = true;
	}
}

void Timer::pause()
{
	if (isRunning) {
		isPaused = true;
		end = steady_clock::now();
		isRunning = false;
	}
}

void Timer::reset()
{
	if (!isRunning) {
		beg = end;
	} else {
		beg = steady_clock::now();
	}
}

bool Timer::active() const {
	return isRunning;
}


double Timer::timeElapsed()
{
	nanoseconds duration;
	if (isRunning) {
		duration = steady_clock::now() - beg;
	} else {
		duration = end - beg;
	}
	return static_cast<double>(duration.count()) / 1e9;
}

int64_t Timer::timeElapsed_s()
{
	nanoseconds duration;
	if (isRunning) {
		duration = steady_clock::now() - beg;
	} else {
		duration = end - beg;
	}
	return std::chrono::duration_cast<seconds>(duration).count();
}

int64_t Timer::timeElapsed_m()
{
	nanoseconds duration;
	if (isRunning) {
		duration = steady_clock::now() - beg;
	} else {
		duration = end - beg;
	}
	return std::chrono::duration_cast<milliseconds>(duration).count();
}

int64_t Timer::timeElapsed_mc()
{
	nanoseconds duration;
	if (isRunning) {
		duration = steady_clock::now() - beg;
	} else {
		duration = end - beg;
	}
	return std::chrono::duration_cast<microseconds>(duration).count();
}

int64_t Timer::timeElapsed_n()
{
	nanoseconds duration;
	if (isRunning) {
		duration = steady_clock::now() - beg;
	} else {
		duration = end - beg;
	}
	return std::chrono::duration_cast<nanoseconds>(duration).count();
}