#pragma once
#include <chrono>

class Timer {
private:
	std::chrono::steady_clock::time_point m_t;
	std::chrono::duration<double, std::milli> m_duration;

public:
	Timer() {
		m_t = std::chrono::high_resolution_clock::now();
		m_duration = std::chrono::duration<double, std::milli>(0);
	}

	//start timer
	inline void start() { 
		m_t = std::chrono::high_resolution_clock::now();
	}

	//stop timer and get time from timer in millisec
	inline double stop() {
		m_duration = std::chrono::high_resolution_clock::now() - m_t;
		return m_duration.count();
	}

	//returns duration of timer in milliseconds since start() was called
	inline double getCurrentDuration() {
		return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - m_t).count();
	}

	//get duration of timer in milliseconds
	//call stop() before this
	inline double getDuration() {
		return m_duration.count();
	}

	//get time since betriebszeit in milliseconds
	static inline long long getTime() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	}
};