#include "keyboard.hpp"

keyboard::keyboard(hwlib::keypad<16> & keypad):
	keypad(keypad)
{}

keyboard::keyboard(keyboard & existingKeyboard):
	keypad(existingKeyboard.keypad)
{}

void keyboard::update(){
	if(keypad.char_available()){
		if(hwlib::now_us() - lastKeyPress > 1'000'000){
			lastKeyPress = hwlib::now_us();
			characterBuffer[bufferLength] = keypad.getc();
			bufferLength++;
		} else if(hwlib::now_us() - lastKeyPress < 500'000 && hwlib::now_us() - lastKeyPress > 260'000){
			lastKeyPress = hwlib::now_us();
			if(characterBuffer[bufferLength] < 97){
				characterBuffer[bufferLength] = (((keypad.getc() - '0') - 1) * 3) + 97;
			} else {
				characterBuffer[bufferLength]++;
			}
			hwlib::cout << "Doublepress!" << hwlib::endl;
			hwlib::wait_us(50);
			while(keypad.char_available()){
				hwlib::wait_us(50);
			}
		}
	}
}

char keyboard::readChar(){
	return keypad.getc();
}

bool keyboard::charAvailable(){
	return keypad.char_available();
}

unsigned int keyboard::currentBufferSize(){
	return bufferLength;
}

char keyboard::getBufferElement(const int position){
	if(position >= 0 && position < 10){
		return characterBuffer[position];
	} else {
		return 0;
	}
}

void keyboard::clearBuffer(){
	bufferLength = 0;
}

void keyboard::debug(){
   	int n = 0;
   	for(;;){
	   	if(keypad.char_available()){
	   		hwlib::cout << n++ << " [" << keypad.getc() << "]\n";
	   	}
   	}
}