#ifndef __KEYPAD_HPP
#define __KEYPAD_HPP

#include <array>
#include "hwlib.hpp"

class keyboard {
	private:
		hwlib::keypad<16> & keypad;

		uint_fast64_t lastKeyPress;
		uint_fast64_t keyPressPeriod;

		char lastCharacter;
		char newCharacter;
	public:
		keyboard(hwlib::keypad<16> & keypad);
		keyboard(keyboard & existingKeyboard);

		void update();
		char readChar();
		bool charAvailable();

		void debug();
};

#endif //__KEYPAD_HPP