#ifndef __TRANSMITTER_HPP
#define __TRANSMITTER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class infraredTransmitter : public rtos::task<> {
private:
   	hwlib::target::d3_38kHz transmitter = hwlib::target::d3_38kHz();

   	rtos::clock transmitClock;
   	rtos::channel<uint16_t, 50> messageChannel;

   	uint32_t dataToTransmit;
   	int bitsToSend;

   	uint8_t controlBits;
   	bool hasBeenControlled;

   	uint_fast64_t startedTime;
   	uint_fast64_t transmittedDuration;
   	uint_fast64_t highDuration;
   	uint_fast64_t lowTransmittedDuration;
   	uint_fast64_t lowDuration;

   	enum class states {IDLE, COMMUNICATING};
   	states state = states::IDLE;
   	enum class substates {IDLE, TRANSMITTING, NOT_TRANSMITTING, CONTROLLING};
   	substates substate = substates::IDLE;
public:
	infraredTransmitter();

	void main() override;

   	void sendData(const uint16_t data);
   	uint8_t calculateControlBits(const uint16_t data);
};

#endif //__TRANSMITTER_HPP