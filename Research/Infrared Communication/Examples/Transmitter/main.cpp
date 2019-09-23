#include "hwlib.hpp"
#include "transceiver.hpp"

int main( void ){	
	hwlib::wait_ms( 500 );

	auto irTransmitter = transmitter();

	const uint16_t data = 65333;

   	for(;;){
    	irTransmitter.sendChar(data);
		hwlib::wait_ms(2000);
   	}
}
