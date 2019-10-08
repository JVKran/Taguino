#include "message.hpp"

messageDecoder::messageDecoder(messageListener & listener):
	listener(listener),
	pauses(this, "Pause Channel")
{
	state = states::idle;
}

void messageDecoder::pauseDetected(const uint_fast64_t pause){
	int miliSec = pause /1000;
	hwlib::cout<<"pauseDetected "<<miliSec<<" Mili Seconden\n";
	pauses.write(pause);
}

void messageDecoder::main(){
	for(;;){
		auto event = wait(pauses);
		if(event == pauses){
			auto readDuration = pauses.read()/1000;		//Convert readDuration to miliseconds
			hwlib::cout<<"ReadDuration: "<<readDuration<<hwlib::endl;
			switch(state){
				case states::idle:
					if(readDuration > 4000 && readDuration < 5000){
						hwlib::cout<<"Idle correcte timing\n";
						state = states::message;
						n = 0;
						m = 0;
					}else{
						hwlib::cout<<"In de else loop van IDLE\n";
					}
					break;
				case states::message:
					if(readDuration > 200 && readDuration < 2000){
						state = states::idle;
						hwlib::cout<<"Message correcte timing\n";
					} else {
						hwlib::cout<<"In de else loop van MESSAGE\n";
						n++;
						m = m << 1;
						m|=(readDuration > 1000)?1:0;
						if(n == 0){
							state = states::idle;
							listener.messageReceived(m);
							hwlib::cout<<"messageRecieved\n";
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

