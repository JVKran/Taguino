#include "message.hpp"

messageDecoder::messageDecoder(const pauseListener & listener):
	listener(listener)
{}

void messageDecoder::pauseDetected(const uint_fast64_t pause){
	pauses.write(pause);
}

void messageDecoder::main(){
	auto event = wait(pauses);
	if(event == pauses){
		if()
	}
}

