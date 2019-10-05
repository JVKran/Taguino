#ifndef __PAUSE_HPP
#define __PAUSE_HPP

#include "rtos.hpp"

class pauseDetector : public rtos::task<> {
	private:
		hwlib::target::pin_in & irReceiver;
		pauseListener & listener;
		rtos::clock sampleClock;
		rtos::channel<int, 1024> detectedPauses;

		uint_fast64_t measuredDuration;
		uint_fast64_t pauseDuration;
		uint_fast64_t getPauseDuration();
	public:
		pauseDetector(hwlib::target::pin_in & irReceiver, pauseListener & listener, long long duration, const char * name);

		void main() override;
};

class pauseListener {
	public:
		void pauseDetected(const uint_fast64_t pause) = 0;
};


#endif //__PAUSE_HPP