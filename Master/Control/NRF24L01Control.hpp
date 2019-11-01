#ifndef __NRF24L01CONTROL_HPP
#define __NRF24L01CONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class NRF24L01Control : public NRFControl, public rtos<>{
private:
	NRF24L01& nrf;

public:

	NRF24L01Control();

	void startListening();
	void read();
	void readFast();
	void startWriting();
	void send();
	void sendFast();
	void main();

};

#endif //__NRF24L01CONTROL_HPP