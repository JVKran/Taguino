#include "hwlib.hpp"
#include "transceiver.hpp"

transmit::transmit(hwlib::pin_out & transmitPin):
	transmitPin(transmitPin)
{}


//Eerst hoog dan laag = 1
//Eerst laag dan hoog = 0
//Een verzoek door 1, dan 1 door ontvanger, dan verzenden.
void transmit::send(const uint16_t content){
	hwlib::cout << "Start-Sequence: ";
	sendBit(1);
	sendBit(1);
	sendBit(0);
	sendBit(1);
	hwlib::cout << hwlib::endl << "Content: ";
	for(unsigned int i = 0; i < 15; i++){
		sendBit(content & (1 << i));
	}
	transmitPin.write(0);
	transmitPin.flush();
	hwlib::cout << hwlib::endl << hwlib::endl;
}

void transmit::sendBit(const bool bit){
	transmitPin.write(bit);
	transmitPin.flush();
	hwlib::cout << bit;
	hwlib::wait_us_busy(416);
	transmitPin.write(!bit);
	transmitPin.flush();
	hwlib::wait_us_busy(416);
}

//------------------------------------------------------------//

receive::receive(hwlib::pin_in & receivePin):
	receivePin(receivePin)
{}

//------------------------------------------------------------//

transceiver::transceiver(transmit & transmitter, receive & receiver):
	transmitter(transmitter),
	receiver(receiver)
{}