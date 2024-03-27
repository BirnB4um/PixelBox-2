#pragma once
#include <chrono>

class Timer {
private:
	std::chrono::steady_clock::time_point m_t;
	std::chrono::duration<double, std::milli> m_duration;

public:
	//start timer
	void start() { m_t = std::chrono::high_resolution_clock::now(); }

	//stop timer and get time from timer in millisec
	double stop() {
		m_duration = std::chrono::high_resolution_clock::now() - m_t;
		return m_duration.count();
	}

	//get duration of timer in milliseconds
	double getDuration() { return m_duration.count(); }

	//get time since betriebszeit in milliseconds
	long long getTime() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	}
};