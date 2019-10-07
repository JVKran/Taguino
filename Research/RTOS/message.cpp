#include "message.hpp"

messageDecoder::messageDecoder(messageListener & listener):
	listener(listener),
	pauses(this, "Pause Channel")
{}

void messageDecoder::pauseDetected(const uint_fast64_t pause){
	pauses.write(pause);
}

void messageDecoder::main(){
	for(;;){
		auto event = wait(pauses);
		if(event == pauses){
			auto readDuration = pauses.read();
			switch(state){
				case states::idle:
					if(readDuration > 4000 && readDuration < 5000){
						state = states::message;
						n = 0;
						m = 0;
					}
					break;
				case states::message:
					if(readDuration > 200 && readDuration < 2000){
						state = states::idle;
					} else {
						n++;
						m = m << 1;
						//m|(readDuration > 1000)?1:0;
						if(n == 15){
							state = states::idle;
							listener.messageReceived(m);
							hwlib::cout << m << hwlib::endl;
						}
						break;
					}
			}
		}
	}
}

//<<<<<<<<<<<<<<<<<<<------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>

messageLogger::messageLogger(const char * name):
	task(name),
	messages(this, "Message Channel"),
	clearDisplayTimer(this, "Clear Display Timer")
{}

void messageLogger::main(){
	for(;;){
		auto event = wait(messages + clearDisplayTimer);
		if(event == messages){
			hwlib::cout << messages.read() << hwlib::endl;
			clearDisplayTimer.set(5'000'000);
		} else {
			hwlib::cout << "Cleared Display" << hwlib::endl;
		}
	}
}

