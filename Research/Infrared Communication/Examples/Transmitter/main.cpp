#include "hwlib.hpp"
#include "transmitter.hpp"

#include <array>

int main( void ){	
	hwlib::wait_ms( 500 );

	auto irTransmitter = transmitter();
	const uint16_t data = 43643;

   	for(;;){
   		irTransmitter.sendData(data);
   		hwlib::wait_ms(100);
   	}
}
