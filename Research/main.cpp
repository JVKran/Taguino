#include "hwlib.hpp"
#include "transceiver.hpp"

int main(){
	auto FS1000A = hwlib::target::pin_out( hwlib::target::pins::d7 );
	transmit transmitter(FS1000A);
	hwlib::wait_ms(500);
	hwlib::cout << "Program started." << hwlib::endl;
	uint16_t message = 448;
	transmitter.send(message);
}
