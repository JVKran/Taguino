#include "hwlib.hpp"
#include "transceiver.hpp"

#include <array>

int main( void ){	
	hwlib::wait_ms( 500 );

	auto irTransmitter = transmitter();
	const uint16_t data = 43643;

   	for(;;){
   		irTransmitter.sendData(data);
   		hwlib::cout<<int(data)<<'\n';
   		hwlib::wait_ms(100);
   	}
}
