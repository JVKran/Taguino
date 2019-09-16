#ifndef __TRANSCEIVER_HPP
#define __TRANSCEIVER_HPP

#include "hwlib.hpp"

class transmitter {
private:
   	hwlib::target::d2_36kHz transmitter = hwlib::target::d2_36kHz();
public:
   	void sendBit(const bool bit);
   	void sendChar(const char test);
};

class receiver {
private:
	hwlib::target::pin_in irReceiver;

	uint_fast64_t highDuration = 0;
	char receivedChar;
public:
	receiver(hwlib::target::pin_in & irReceiver);

	bool dataAvailable();

	bool readBit();
	char readChar();
};

#endif //__TRANSCEIVER_HPP