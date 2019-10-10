#ifndef __TRANSCEIVER_HPP
#define __TRANSCEIVER_HPP

#include "hwlib.hpp"

class transmitter {
private:
   	//hwlib::target::d2_36kHz transmitter = hwlib::target::d2_36kHz();
	hwlib::target::d2_38kHz transmitter = hwlib::target::d2_38kHz();
public:
	void startCondition();

   	void sendBit(const bool bit);
   	void sendChar(const char character);
   	void sendData(const uint16_t data);
};

class receiver {
private:
	hwlib::target::pin_in irReceiver;

	uint_fast64_t highDuration = 0;
	uint_fast64_t lowDuration = 0;

	char receivedChar;
	uint16_t receivedData;
public:
	receiver(hwlib::target::pin_in & irReceiver);

	bool dataAvailable();

	bool readBit();
	char readChar();
	uint16_t readData();

	void debugTerminal();
};

#endif //__TRANSCEIVER_HPP