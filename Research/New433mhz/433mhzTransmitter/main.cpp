#include "433mhz.hpp"
#include "hwlib.hpp"
int main(){
	namespace target = hwlib::target;
	
	//auto receive = target::pin_in ( target::pins::d0 );
	auto transmit = target::pin_out ( target::pins::d14 );

	auto sw = target::pin_in ( target::pins::d3 );

	auto transmitIt = transmitter( transmit );

	//auto receiveIt = receiver( receive );
	
	for(;;){
		uint8_t c = 1;
		hwlib::wait_ms(1);
		if( !sw.read() ){
			hwlib::wait_ms(100);
			hwlib::cout<<"Writing " << c<<"\n";
			transmitIt.writeUint(c);
			//hwlib::cout<< receiveIt.readUint(true)<<"\n";
			
		}
		
	}
}
