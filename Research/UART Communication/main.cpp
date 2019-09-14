#include "hwlib.hpp"
#include "transceiver.hpp"

int main(){
	auto ledPin = hwlib::target::pin_out(hwlib::target::pins::d7);
	auto led = transmitter(ledPin);

	for(;;){
		led.transmit('h');
		hwlib::wait_ms(2000);
	}
}