#include "hwlib.hpp"
#include "HCSR04.hpp"

int main(){
   	auto triggerPin = hwlib::target::pin_out(hwlib::target::pins::d49);
   	auto echoPin = hwlib::target::pin_in(hwlib::target::pins::d47);
	auto distanceSensor = HCSR04(triggerPin, echoPin);

	//Wait for terminal
	hwlib::wait_ms(500);

	for(;;){
		hwlib::cout << "Distance: " << hwlib::setw(5) << distanceSensor.getDistance() << hwlib::endl;
		hwlib::wait_ms(1000);
	}
}