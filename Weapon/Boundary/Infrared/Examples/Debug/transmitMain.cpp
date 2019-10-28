#include "hwlib.hpp"
#include "transceiver.hpp"

#include <array>

int main( void ){	
	hwlib::wait_ms( 500 );

	auto irTransmitter = transmitter();

	std::array<char, 6> word = {'j', 'a', 'w', 'o', 'e', 'l'};

   	for(;;){
   		for(const auto & character : word){
   			irTransmitter.sendChar(character);
   			hwlib::wait_ms(500);
   		}
   	}
}
