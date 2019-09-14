#include "hwlib.hpp"
#include "transceiver.hpp"

transmitter::transmitter(hwlib::pin_out & transmitPin):
	transmitPin(transmitPin)
{}

void transmitter::transmit(const char value){
	hwlib::uart_putc_bit_banged_pin(value, transmitPin);
}
