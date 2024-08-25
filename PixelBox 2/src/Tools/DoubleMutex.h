#pragma once
#include <mutex>

class DoubleMutex {
public:

	DoubleMutex() : m_locked(false) {}

	~DoubleMutex() {}

	void lock() {
		m_nextAccessMutex.lock();
		m_dataMutex.lock();
		m_nextAccessMutex.unlock();
		m_locked = true;
	}

	void unlock() {
		if (m_locked) {
			m_locked = false;
			m_dataMutex.unlock();
		}
	}

	inline bool isLocked() { return m_locked; }

private:
	std::mutex m_nextAccessMutex;
	std::mutex m_dataMutex;
	bool m_locked;
};

class DoubleMutexGuard {
public:

	DoubleMutexGuard(DoubleMutex& mutex) {
		m_mutex = &mutex;
		m_mutex->lock();
	}

	~DoubleMutexGuard() {
		m_mutex->unlock();
	}

private:
	DoubleMutex* m_mutex;
};