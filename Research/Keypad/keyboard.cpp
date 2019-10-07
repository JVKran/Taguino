#include "keyboard.hpp"

keyboard::keyboard(hwlib::keypad<16> & keypad):
	keypad(keypad)
{}

keyboard::keyboard(keyboard & existingKeyboard):
	keypad(existingKeyboard.keypad)
{}

void keyboard::update(){
	newCharacter = keypad.pressed();
	if(newCharacter != '\0'){
		keyPressPeriod = hwlib::now_us() - lastKeyPress;
		lastKeyPress = hwlib::now_us();
		lastCharacter = newCharacter;
		hwlib::wait_ms(200);
		while(hwlib::now_us() - lastKeyPress < 1'000'000){
			newCharacter = keypad.pressed();
			if(newCharacter != '\0'){
				lastCharacter++;
				lastKeyPress = hwlib::now_us();
				hwlib::wait_ms(200);
			}
		}
		hwlib::cout << lastCharacter << hwlib::endl;
	}	
}

char keyboard::readChar(){
	return keypad.pressed();
}

void keyboard::debug(){
   	int n = 0;
   	for(;;){
	   	if(keypad.char_available()){
	   		hwlib::cout << n++ << " [" << keypad.getc() << "]\n";
	   	}
   	}
}