#include "keyboard.hpp"

keyboard::keyboard(hwlib::keypad<16> & keypad):
	keypad(keypad)
{}

keyboard::keyboard(keyboard & existingKeyboard):
	keypad(existingKeyboard.keypad)
{}

void keyboard::update(){
	if(keypad.char_available()){
		bufferLength++;
		characterBuffer[bufferLength] = keypad.getc();
	}
}

char keyboard::readChar(){
	if(keypad.char_available()){
		return keypad.getc();
	} else {
		return 0;
	}
}

bool keyboard::charAvailable(){
	return keypad.char_available();
}

int keyboard::currentBufferSize(){
	return bufferLength;
}

char keyboard::getBufferElement(const int position){
	if(position >= 0 && position < 5){
		return characterBuffer[position];
	} else {
		return 0;
	}
}

void keyboard::debug(){
   	int n = 0;
   	for(;;){
	   	if(keypad.char_available()){
	   		hwlib::cout << n++ << " [" << keypad.getc() << "]\n";
	   	}
   	}
}