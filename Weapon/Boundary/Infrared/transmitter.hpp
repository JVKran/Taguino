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
	uint_fast64_t highStartTime;
	uint_fast64_t highDuration;
	uint_fast64_t lowStartTime;
	uint_fast64_t lowDuration;

	enum class states {IDLE, COMMUNICATING};
	states state = states::IDLE;

	enum class substates {IDLE, HIGH_TRANSMITTING, LOW_TRANSMITTING, CONTROLLING, SENDING};
	substates substate = substates::IDLE;
	substates previousSubstate = substates::IDLE;
public:
	infraredTransmitter(const long long int period = 100);

	void main() override;

   	void sendData(const uint16_t data);
   	uint8_t calculateControlBits(const uint16_t data);
};

#endif //__TRANSMITTER_HPP