#ifndef __HC_SR04_HPP
#define __HC_SR04_HPP

class HCSR04{
private:
	hwlib::pin_out & triggerPin;
	hwlib::pin_in & echoPin;
	uint_fast64_t echoStartTime;
	uint_fast64_t echoEndTime;
public:
	HCSR04(hwlib::pin_out & triggerPin, hwlib::pin_in & echoPin);
	HCSR04(HCSR04 & existingSensor);

	const unsigned int getDistance(const bool resultInInches = false);
};


#endif //__HC_SR04_HPP