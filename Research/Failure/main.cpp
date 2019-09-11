#include "hwlib.hpp"
#include "transceiver.hpp"

int main(){
	auto FS1000A = hwlib::target::pin_out( hwlib::target::pins::d7 );
	auto SRX822 = hwlib::target::pin_in( hwlib::target::pins::d8 );

	transmit transmitter(FS1000A);
	receive receiver(SRX822);

	uint16_t message = 65534;

	hwlib::wait_ms(500);
	hwlib::cout << "Program started." << hwlib::endl;

	for(;;){
		transmitter.send(message);
		hwlib::wait_ms(5000);
	}
	
}

/*
Is 8 bit-communication possible?
PPPAAPPP
00101010 = Player 1 shot player 2
00111100 = Player 1 captured flag from player 4
00110100 = player 1 got exploded by player 4
00100100 = player 
and more communication about gameplay; so 16 bit needed...

8 players
4 actions
8 players
answer: NO

Sketch of protocol:
Slave -> Master
Eerst tijdje hoog, dan heel kort laag om te kijken of het laag blijft. Dan maakt de master hem na vastgestelde tijd weer hoog om slave te selecteren.

Master -> Slaves
Eerst tijdje hoog, dan heel kort laag om te kijken of het laag blijft. Dan begint de communicatie.
*/