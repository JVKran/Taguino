#include "message.hpp"

messageDecoder::messageDecoder(messageListener & listener):
	listener(listener),
	pauses(this, "Pause Channel")
{
	state = states::idle;
}

void messageDecoder::pauseDetected(const int n){
	pauses.write(n);
}

void messageDecoder::main(){
	for(;;){
		wait(pauses);
		auto p = pauses.read();
		switch(state){
			case states::idle:
				if(p > 4000 && p < 5000){
					state = states::message;
					n = 0;
					m = 0;
				}
				break;
			case states::message:
				if(p > 200 && p < 2000){
					n++;
					m = m << 1;
					m|=(p > 1000) ? 1 : 0;
					if(n == 15){
						state = states::idle;
						listener.messageReceived(m);
					}
				} else {
					state = states::idle;
				}
				break;
		}
	}
}

//<<<<<<<<<<<<<<<<<<<------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>

messageLogger::messageLogger(hwlib::i2c_bus_bit_banged_scl_sda & bus, const char * name):
	task(name),
	bus(bus),
	oled(hwlib::glcd_oled(bus)),
	messages(this, "Message Channel"),
	clearDisplayTimer(this, "Clear Display Timer")
{
	oled.clear();
	oled.flush();
}

void messageLogger::main(){
	for(;;){
		auto event = wait(messages + clearDisplayTimer);
		if(event == messages){
			// messageTerminal << "\f" << messages.read() << hwlib::flush;
			hwlib::cout << messages.read() << hwlib::endl;
			clearDisplayTimer.set(5'000'000);
		} else {
			messageTerminal << "\f     " << hwlib::flush;
		}
	}
}

