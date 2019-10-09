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
			switch(state){
				case states::idle:
					if(!irReceiver.read()){	//If the transmit pin is high
						listener.pauseDetected(pauseDuration);
						//hwlib::cout << "listener.pauseDetected(" << pauseDuration << ");" << hwlib::endl;
						state = states::signal;
					} else {
						pauseDuration+=100;
					}
					break;
				case states::signal:
					if(irReceiver.read()){
						state = states::idle;
						pauseDuration = 0;
					}
					break;
			}
		}		
	}
}	
