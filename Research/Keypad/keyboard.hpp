#ifndef __KEYPAD_HPP
#define __KEYPAD_HPP

#include <array>
#include "hwlib.hpp"

class keyboard {
	private:
		hwlib::keypad<16> & keypad;

		uint_fast64_t lastKeyPress;
		uint_fast64_t keyPressPeriod;

		char lastCharacter;				//Lastly returned char; after T9-Simulation.
		char lastKey;					//Lastly pressed key; before T9-Simulation.
		char newCharacter;				//Newly received char; before T9-Simulation (result of getc())
		unsigned int letterIncrements;	//Amount of double presses; equal to amount of increments (from a to b and c).
	public:
		keyboard(hwlib::keypad<16> & keypad);
		keyboard(keyboard & existingKeyboard);

		char readChar();
		char readKey();

		void debug();
};

#endif //__KEYPAD_HPP