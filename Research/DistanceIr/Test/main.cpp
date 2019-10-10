#include "hwlib.hpp"
#include "transceiver.hpp"
#include "HCSR04.hpp"

int main( void ){	
	hwlib::wait_ms( 500 );

	auto triggerPin = hwlib::target::pin_out(hwlib::target::pins::d49);
   	auto echoPin = hwlib::target::pin_in(hwlib::target::pins::d47);
	auto distanceSensor = HCSR04(triggerPin, echoPin);

	auto irTransmitter = transmitter();

	uint8_t dist = 0;
	int8_t health = 80;
	uint16_t data = 0;

   	for(;;){
   		data = 0000;
		dist = distanceSensor.getDistance();
		data |= dist;
		data |= health << 8;
		health-=10;

		hwlib::cout << "Distance: " << (data & 255) << hwlib::endl << "Health: " << ((data & 0xFF00) >> 8) << hwlib::endl << hwlib::endl;
		transmitter.sendData(data);

		hwlib::wait_ms(1000);
		
		if(health <= 0){
			hwlib::cout << "You died..." << hwlib::endl;
			break;
		}
   	}
}
