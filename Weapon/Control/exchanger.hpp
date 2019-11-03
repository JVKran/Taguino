#ifndef __EXCHANGER_HPP
#define __EXCHANGER_HPP

#include "game.hpp"
#include "NRF24.hpp"

class exchangeGameData : public radioListener {
private:
	runGame & game;

	hwlib::target::pin_out csn  = hwlib::target::pin_out( hwlib::target::pins::d30 );
   	hwlib::target::pin_out ce   = hwlib::target::pin_out( hwlib::target::pins::d32 );

	NRF24 radio;
public:
	exchangeGameData(runGame & game, hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBus, const long long int duration);

	virtual void dataReceived(const uint8_t data[], const int len) override{
		for(int i = 0; i < len; i++){
			hwlib::cout << data[i] << " ";
		}
		hwlib::cout << hwlib::endl;
	}

};



#endif //__EXCHANGER_HPP