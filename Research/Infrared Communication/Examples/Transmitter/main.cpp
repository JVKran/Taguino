#include "hwlib.hpp"
#include "transceiver.hpp"

#include <array>

int main( void ){	
	hwlib::wait_ms( 500 );

	auto irTransmitter = transmitter();
	const uint16_t data = 43695;

   	for(;;){
   		irTransmitter.sendData(data);
   		hwlib::wait_ms(500);
   	}
}
