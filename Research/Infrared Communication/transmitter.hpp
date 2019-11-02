#ifndef __TRANSMITTER_HPP
#define __TRANSMITTER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class infraredTransmitter : public rtos::task<> {
private:
   	hwlib::target::d3_38kHz transmitter = hwlib::target::d3_38kHz();

   	rtos::clock transmitClock;
   	rtos::channel<int, 2048> highDurations;
   	unsigned int highDuration;

   	unsigned int transmittedDuration;
   	int lowDuration;

   	enum class states {IDLE, TRANSMITTING, NOT_TRANSMITTING};
   	states state = states::IDLE;
public:
	infraredTransmitter();

	void main() override;

   	void sendBit(const bool bit);
   	void sendStartCondition();
};

class infraredEncoder {
private:
	infraredTransmitter transmitter = infraredTransmitter();
	uint8_t controlBits;
public:
	void sendData(const uint16_t data);
	uint8_t calculateControlBits(const uint16_t data);
};

#endif //__TRANSMITTER_HPP