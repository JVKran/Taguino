#include "pause.hpp"

pauseDetector::pauseDetector(hwlib::target::pin_in & irReceiver, pauseListener & listener, long long duration, const char * name):
	task(name),
	irReceiver(irReceiver),
	listener(listener),
	sampleClock(this, duration, "Sample Clock"),
	detectedPauses(this, "Pause Channel")
{}

//Maybe play with highs and lows...
void pauseDetector::main(){
	n = 0;
	state = states::idle;
	
	for(;;){
		wait(sampleClock);
		switch(state){
			case states::idle:
				if(!irReceiver.read()){	//If the transmit pin is high
					listener.pauseDetected(n);
					//hwlib::cout << "listener.pauseDetected(" << n << ");" << hwlib::endl;
					state = states::signal;
				} else {
					n+=100;
				}
				break;
			case states::signal:
				if(irReceiver.read()){
					state = states::idle;
					n = 0;
				}
				break;
		}	
	}
}	
