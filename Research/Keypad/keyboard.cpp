/// @file
#include "keyboard.hpp"

keyboard::keyboard(hwlib::keypad<16> & keypad):
	keypad(keypad)
{}

keyboard::keyboard(keyboard & existingKeyboard):
	keypad(existingKeyboard.keypad)
{}

/// \brief
/// Read Character
/// \details
/// This function returns the character of the pressed key. It simulates a T9 keyboard
/// in which button 2 can be pressed three times to select letter c. Once to select letter a, etc.
/// It has to know which key has been pressed. This is tored in the lastKey variable. If this is equal
/// to the pressed key, we can increment the char with one if it hasn't been done so for three times
/// already.
char keyboard::readChar(){
	newCharacter = keypad.pressed();
	if(newCharacter != '\0'){
		keyPressPeriod = hwlib::now_us() - lastKeyPress;
		lastKeyPress = hwlib::now_us();
		lastKey = newCharacter;
		lastCharacter = (((newCharacter - '0') - 2) * 3) + 97;
		hwlib::wait_ms(200);
		while(hwlib::now_us() - lastKeyPress < 1'000'000){
			newCharacter = keypad.pressed();
			if(newCharacter != '\0' && letterIncrements < 2 && newCharacter == lastKey){
				lastCharacter++;
				letterIncrements++;
				lastKeyPress = hwlib::now_us();
				hwlib::wait_ms(200);
			} else {
				break; 
			}
		}
		letterIncrements = 0;
		return lastCharacter;
	} else {
		return 0;
	}
}

/// \brief
/// Read Key
/// \details
/// This function returns the character of the pressed key equal to the one drawn on the numpad.
char keyboard::readKey(){
	return keypad.pressed();
}

/// \brief
/// Debug
/// \details
/// This function can be used for debugging. It prints the amount of presses that have been done
/// and the pressed key.
void keyboard::debug(){
   	int n = 0;
   	for(;;){
	   	if(keypad.char_available()){
	   		hwlib::cout << n++ << " [" << keypad.getc() << "]\n";
	   	}
   	}
}