
#include <chrono>

class Timer
{
	typedef std::chrono::seconds seconds;
	typedef std::chrono::milliseconds milliseconds;
	typedef std::chrono::microseconds microseconds;
	typedef std::chrono::nanoseconds nanoseconds;
	typedef std::chrono::steady_clock steady_clock;

public:
	Timer() = default;
	virtual ~Timer() = default;

private:
	steady_clock::time_point beg;
	steady_clock::time_point end;
	bool isRunning = false;
	bool isPaused = false;

public:
	void run();
	void pause();
	void reset();
	bool active() const;

	double timeElapsed();
	int64_t timeElapsed_s();
	int64_t timeElapsed_m();
	int64_t timeElapsed_mc();
	int64_t timeElapsed_n();
};
