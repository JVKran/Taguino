#ifndef __PAUSE_HPP
#define __PAUSE_HPP

#include "rtos.hpp"

class pauseListener {
	public:
		virtual void pauseDetected(const int pause) = 0;
};

class pauseDetector : public rtos::task<> {
	private:
		hwlib::target::pin_in & irReceiver;
		pauseListener & listener;

		rtos::clock sampleClock;
		rtos::channel<int, 1024> detectedPauses;

		enum class states {idle, signal};
		states state;

		int n;
	public:
		pauseDetector(hwlib::target::pin_in & irReceiver, pauseListener & listener, long long duration, const char * name);

		void main() override;
};

#endif //__PAUSE_HPP