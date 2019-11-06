#ifndef __RECEIVER_HPP
#define __RECEIVER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"


class highSignalListener {
public:
	virtual void highSignalDetected(const int highDuration) = 0;
};

class messageListener {
public:
	virtual void messageReceived(const uint16_t message) = 0;
};

class infraredReceiver : public rtos::task<> {
private:
	hwlib::target::pin_in irReceiver = hwlib::target::pin_in(hwlib::target::pins::d5);
	highSignalListener & listener;

	uint_fast64_t highDuration = 0;

	rtos::clock sampleClock;
	const long long period;

	enum class states {IDLE, SIGNAL};
	states state = states::IDLE;
public:
	infraredReceiver(highSignalListener & listener, const long long int period = 100);

	void main() override;
};

class infraredDecoder : public rtos::task<>, public highSignalListener {
private:
	messageListener & listener;

	int highDuration;
	int receivedBits;
	uint16_t receivedData;

	uint8_t controlBits;
	uint8_t receivedControlBits;
	int amountOfControlBits;

	rtos::channel<int, 1024> highDurations;
	enum class states {IDLE, MESSAGE, CONTROL};
	states state = states::IDLE;
public:
	infraredDecoder(messageListener & listener);

	virtual void highSignalDetected(const int highDuration) override;

	uint8_t calculateControlBits(const uint16_t data);

	void main() override;
};

#endif //__RECEIVER_HPP