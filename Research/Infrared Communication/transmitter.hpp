#ifndef __TRANSMITTER_HPP
#define __TRANSMITTER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class infraredTransmitter {
private:
   	hwlib::target::d3_38kHz transmitter = hwlib::target::d3_38kHz();

   	uint8_t controlBits;
public:
	void startCondition();

   	void sendBit(const bool bit, const uint16_t duration = 700);
   	void sendChar(const char character);
   	void sendData(const uint16_t data);

   	uint8_t calculateControlBits(const uint16_t data);
};


#endif //__TRANSMITTER_HPP