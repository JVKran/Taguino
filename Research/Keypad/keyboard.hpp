#ifndef __KEYPAD_HPP
#define __KEYPAD_HPP

#include <array>
#include "hwlib.hpp"

class keyboard {
	private:
		hwlib::keypad<16> & keypad;

		std::array<char, 5> characterBuffer;
		unsigned int bufferLength = 0;
	public:
		keyboard(hwlib::keypad<16> & keypad);
		keyboard(keyboard & existingKeyboard);

		void update();
		char readChar();
		bool charAvailable();

		int currentBufferSize();
		char getBufferElement(const int position);


		void debug();
};

#endif //__KEYPAD_HPP