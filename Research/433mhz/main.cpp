#include "433mhz.hpp"
#include "hwlib.hpp"
int main(){
	namespace target = hwlib::target;
	
	//auto receive = target::pin_in ( target::pins::d0 );
	auto transmit = target::pin_out ( target::pins::d1 );

	auto sw = target::pin_in ( target::pins::d3 );

	auto transmitIt = transmitter( transmit );

	//auto receiveIt = receiver( receive );
	
	for(;;){
		if( !sw.read() ){
			transmitIt.writeUint(1);
			hwlib::wait_ms(50);
			hwlib::cout<<"Writing 1\n";
			//hwlib::cout<< receiveIt.readUint(true)<<"\n";
			hwlib::wait_ms(200);
		}
		
	}
}
