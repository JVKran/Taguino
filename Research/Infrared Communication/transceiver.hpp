#ifndef __TRANSCEIVER_HPP
#define __TRANSCEIVER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class transmitter {
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



class highSignalListener {
public:
	virtual void highSignalDetected(const int highDuration) = 0;
};



class infraredReceiver : public rtos::task<> {
private:
	hwlib::target::pin_in irReceiver = hwlib::target::pin_in(hwlib::target::pins::d5);
	highSignalListener & listener;

	uint_fast64_t highDuration = 0;

	rtos::clock sampleClock;

	enum class states {IDLE, SIGNAL};
	states state = states::IDLE;
public:
	infraredReceiver(highSignalListener & listener);

	void main() override;
};



class infraredDecoder : public rtos::task<>, public highSignalListener {
private:

	int highDuration;
	int receivedBits;
	uint16_t receivedData;

	uint8_t controlBits;
	uint8_t receivedControlBits;

	rtos::channel<int, 1024> highDurations;
	enum class states {IDLE, MESSAGE};
	states state = states::IDLE;
public:
	infraredDecoder();

	virtual void highSignalDetected(const int highDuration) override;

	void main() override;
};

#endif //__TRANSCEIVER_HPP