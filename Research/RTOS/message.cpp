#include "message.hpp"

messageDecoder::messageDecoder(messageListener & listener):
	listener(listener),
	pauses(this, "Pause Channel")
{
	state = states::idle;
}

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
						n++;
						m = m << 1;
						m|=(readDuration > 800) ? 1 : 0;
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
			messageTerminal << "\f" << messages.read() << hwlib::flush;
			clearDisplayTimer.set(5'000'000);
		} else {
			messageTerminal << "\f     " << hwlib::flush;
		}
	}
}

