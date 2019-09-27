#ifndef __KEYPAD_HPP
#define __KEYPAD_HPP

#include <array>
#include "hwlib.hpp"

class keyboard {
	private:
		hwlib::keypad<16> & keypad;

		std::array<char, 10> characterBuffer = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
		unsigned int bufferLength = 0;

		uint_fast64_t lastKeyPress = 0;
	public:
		keyboard(hwlib::keypad<16> & keypad);
		keyboard(keyboard & existingKeyboard);

		void update();
		char readChar();
		bool charAvailable();

		unsigned int currentBufferSize();
		char getBufferElement(const int position);
		void clearBuffer();


		void debug();
};

#endif //__KEYPAD_HPP