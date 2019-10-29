#include "interface.hpp"

interfaceManager::interfaceManager(inputHandler & handler):
	handler(handler),
	rotaryEncoder(KY040(this))
{
	handler.addEncoder(&rotaryEncoder);
}

void interfaceManager::buttonPressed(){
	hwlib::cout << "Encoder Pressed!" << hwlib::endl;
}

void interfaceManager::encoderTurned(const int pos){
	hwlib::cout << "Encoder Turned to position " << pos << "." << hwlib::endl;
}
