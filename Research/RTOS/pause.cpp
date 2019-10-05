#include "pause.hpp"

pauseDetector::pauseDetector(hwlib::target::pin_in & irReceiver, pauseListener & listener, long long duration, const char * name):
	task(name),
	irReceiver(irReceiver),
	listener(listener),
	sampleClock(this, duration, "Sample Clock"),
	detectedPauses(this, "Pause Channel")
{}

void pauseDetector::main(){
	for(;;){
		auto event = wait(sampleClock);
		if(event == sampleClock){
			measuredDuration = getPauseDuration();
			if(measuredDuration > 50){
				listener.pauseDetected(measuredDuration);
				measuredDuration = 0;
			}
		}
	}	
}

uint_fast64_t pauseDetector::getPauseDuration(){
	pauseDuration = hwlib::now_us();
	while(irReceiver.read()){
		irReceiver.refresh();
		hwlib::wait_us(50);
	}
	pauseDuration = hwlib::now_us() - pauseDuration;
	return pauseDuration;
}