#include "hwlib.hpp"
#include "HCSR04.hpp"

int main(){
	namespace target = hwlib::target;
   	auto triggerPin = target::pin_out(target::pins::d8);
   	auto echoPin = target::pin_in(target::pins::d9);
	auto distanceSensor = HCSR04(triggerPin, echoPin);

	//Wait for terminal
	hwlib::wait_ms(500);

	for(;;){
		hwlib::cout << "Distance: " << hwlib::setw(5) << distanceSensor.getDistance() << hwlib::endl;
		hwlib::wait_ms(1000);
	}
}