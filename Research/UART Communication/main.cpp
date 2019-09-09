#include "hwlib.hpp"
#include "transceiver.hpp"

int main(){
	auto FS1000A = hwlib::target::pin_out( hwlib::target::pins::d7 );
	auto SRX822 = hwlib::target::pin_in( hwlib::target::pins::d8 );
	transmit transmitter(FS1000A);
	receive receiver(SRX822);
	hwlib::wait_ms(500);
	hwlib::cout << "Program started." << hwlib::endl;
	uint16_t message = 448;
	transmitter.send(message);
	for(;;){
		hwlib::cout << receiver.read() << hwlib::endl;
		hwlib::wait_ms(100);
	}
}

/*
PPPAAPPP
00101010 = Player 1 shot player 2
00111100 = Player 1 captured flag from player 4
00110100 = player 1 got exploded by player 4
00100100 = player 
and more communication about gameplay; so 16 bit needed...

8 players
4 actions
8 players



*/
