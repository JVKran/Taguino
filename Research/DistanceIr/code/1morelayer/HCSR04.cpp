/// @file

#include "hwlib.hpp"
#include "HCSR04.hpp"

/// \brief
/// Constructor
/// \details
/// This constructor takes one pin_out and one pin_in. These are the trig_pin and
/// echo_pin respectively.
HCSR04::HCSR04(hwlib::pin_out & triggerPin, hwlib::pin_in & echoPin):
	triggerPin(triggerPin),
	echoPin(echoPin)
{}

/// \brief
/// Copy Constructor
/// \details
/// This constructor creates a new object from an already existing object.
HCSR04::HCSR04(HCSR04 & existingSensor):
	triggerPin(existingSensor.triggerPin),
	echoPin(existingSensor.echoPin)
{}

/// \brief
/// Get Distance
/// \details
/// This function returns the distance in centimeters. The triggerpin is first made
/// low to be sure a clean signal is made when it is made high 5us later. The datasheet
/// specifies the signal has to be high for at least 10us. The speed of sound is equal to
/// 1 cm per 29us hence the distance can be calculated as implemented.
const unsigned int HCSR04::getDistance(const bool resultInInches){
	triggerPin.write(0);
	triggerPin.flush();
	hwlib::wait_us(2);
	triggerPin.write(1);
	triggerPin.flush();
	hwlib::wait_us(10);
	triggerPin.write(0);
	triggerPin.flush();
	echoStartTime = hwlib::now_us();
	while(!echoPin.read()){
		echoPin.refresh();
	}
	while(echoPin.read()){
		echoPin.refresh();
	}
	echoEndTime = (hwlib::now_us() - echoStartTime);
	return (resultInInches) ? ((echoEndTime*0.0133)/2) : ((echoEndTime*0.034)/2);
}