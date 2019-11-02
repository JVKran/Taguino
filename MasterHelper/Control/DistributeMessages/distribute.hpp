#ifndef	_DISTRIBUTE_HPP
#define _DISTRIBUTE_HPP

#include <array>
#include "hwlib.hpp"
#include "NRF24.hpp"

class transceiveMessage : public NRF24{
private:
	hwlib::spi_bus & bus; 
	hwlib::pin_out & ce;
	hwlib::pin_out & csn;
	uint8_t adress[5] = { 0x04, 0x00, 0x00, 0x00, 0x00 }
	uint8_t adress1[5] = { 0x00, 0x02, 0x03, 0x04, 0x05 }
public:
	transceiveMessage( hwlib::spi_bus & bus, hwlib::pin_out & ce, hwlib::pin_out & csn );
	void writeMSG( uint8_t val, uint8_t len );
	void readMSG();
};

#endif //DISTRIBUTE_HPP