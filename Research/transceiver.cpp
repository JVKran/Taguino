#include "hwlib.hpp"
#include "transceiver.hpp"

transmit::transmit(hwlib::pin_out & transmitPin):
	transmitPin(transmitPin)
{}

void transmit::send(const uint16_t & content){
	hwlib::uart_putc_bit_banged_pin((content & 0xFF00) >> 8, transmitPin);
	hwlib::uart_putc_bit_banged_pin(content & 0x00FF, transmitPin);
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