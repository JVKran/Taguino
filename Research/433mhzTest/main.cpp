#include "433mhz.hpp"
#include "hwlib.hpp"
int main(){
	namespace target = hwlib::target;
	
	auto receive = target::pin_in ( target::pins::d0 );
	//auto transmit = target::pin_out ( target::pins::d1 );

	//auto sw = target::pin_in ( target::pins::d6 );

	//auto transmitIt = transmitter( transmit );

	auto receiveIt = receiver( receive );
	
	for(;;){
		//transmitIt.writeUint('B');
		hwlib::cout << "nothing\n";
		hwlib::wait_ms(100);
		//hwlib::cout<< receiveIt.readUint(true)<<"\n";
		hwlib::cout<<receiveIt.readUint(true);
		hwlib::wait_ms(100);
	}
}
