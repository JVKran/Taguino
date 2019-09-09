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

bool receive::available(){
	return (uart_getc_bit_banged_pin(receivePin) != 0);
}

uint16_t receive::read(){
	return (uart_getc_bit_banged_pin(receivePin) + (uart_getc_bit_banged_pin(receivePin) >> 8));
}

//------------------------------------------------------------//

transceiver::transceiver(transmit & transmitter, receive & receiver):
	transmitter(transmitter),
	receiver(receiver)
{}