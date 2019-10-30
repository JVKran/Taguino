#ifndef __TRANSCEIVER_HPP
#define __TRANSCEIVER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class receiverListener {
	public:
		virtual void dataReceived(const uint16_t data) = 0;
};

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
	rtos::clock pollClock;
	hwlib::target::pin_in irReceiver;
	receiverListener * listener;

	uint_fast64_t highDuration = 0;
	uint_fast64_t lowDuration = 0;

	char receivedChar;
	uint16_t receivedData;

	uint8_t controlBits;
	uint8_t receivedControlBits;

	uint8_t calculateControlBits(const uint16_t data);

	bool readBit(const uint16_t duration = 800);

	rtos::clock;
public:
	receiver(hwlib::target::pin_in & irReceiver, receiverListener * receivedListener);

	bool dataAvailable();
	char readChar();
	uint16_t readData();

	void debugTerminal();

	void main() override;
};

#endif //__TRANSCEIVER_HPP