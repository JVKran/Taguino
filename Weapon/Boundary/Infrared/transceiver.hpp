#ifndef __TRANSCEIVER_HPP
#define __TRANSCEIVER_HPP

#include "hwlib.hpp"

class transmitter {
private:
   	hwlib::target::d2_38kHz transmitter = hwlib::target::d2_38kHz();

   	uint8_t controlBits;
public:
	void startCondition();

   	void sendBit(const bool bit, const uint16_t duration = 700);
   	void sendChar(const char character);
   	void sendData(const uint16_t data);

   	uint8_t calculateControlBits(const uint16_t data);
};

class receiver : public rtos::task<> {
private:
	hwlib::target::pin_in irReceiver;

	uint_fast64_t highDuration = 0;
	uint_fast64_t lowDuration = 0;

	char receivedChar;
	uint16_t receivedData;

	uint8_t controlBits;
	uint8_t receivedControlBits;

	bool readBit(const uint16_t duration = 800);

	rtos::clock;
public:
	receiver(hwlib::target::pin_in & irReceiver);

	bool dataAvailable();
	char readChar();
	uint16_t readData();

	void debugTerminal();

	uint8_t calculateControlBits(const uint16_t data);

	void main() override;
};

#endif //__TRANSCEIVER_HPP