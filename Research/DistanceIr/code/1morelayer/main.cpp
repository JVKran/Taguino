#include "hwlib.hpp"
#include "transceiver.hpp"
#include "HCSR04.hpp"

int main( void ){	
	hwlib::wait_ms( 500 );
	auto triggerPin = hwlib::target::pin_out(hwlib::target::pins::d49);
   	auto echoPin = hwlib::target::pin_in(hwlib::target::pins::d47);
	auto distanceSensor = HCSR04(triggerPin, echoPin);

	auto irTransmitter = transmitter();

	uint16_t data = 0000;
	const uint8_t lives = 9;
	auto dist = 0;
	//distanceSensor.getDistance();
	data |= dist;
	data |= lives >>9;

   	for(;;){
    	irTransmitter.sendData(data);
		hwlib::cout <<data;
		hwlib::wait_ms(2000);
   	}
}
