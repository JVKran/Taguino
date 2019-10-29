#include "interface.hpp"

interfaceManager::interfaceManager(inputHandler & handler):
	handler(handler),
	rotaryEncoder(KY040(this)),
	encoderPressedFlag(this),
	resetPositionFlag(this),
	newPositionFlag(this),
	positionPool("New Position Pool")
{
	handler.addEncoder(&rotaryEncoder);
}

void interfaceManager::buttonPressed(){
	encoderPressedFlag.set();
}

void interfaceManager::encoderTurned(const int pos){
	newPositionFlag.set();
	positionPool.write(pos);
}

void interfaceManager::main(){
	for(;;){
		auto event = wait(newPositionFlag+encoderPressedFlag);
		if(event == newPositionFlag){
			hwlib::cout << "Encoder Turned to position " << positionPool.read() << "." << hwlib::endl;
		} else {
			hwlib::cout << "Encoder Pressed!" << hwlib::endl;
		}
	}

}
