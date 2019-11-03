#ifndef __EXCHANGER_HPP
#define __EXCHANGER_HPP

#include "NRF24.hpp"
class runGame;

class exchangeGameData : public radioListener {
private:
	runGame * game;

	hwlib::target::pin_out csn  = hwlib::target::pin_out( hwlib::target::pins::d30 );
   	hwlib::target::pin_out ce   = hwlib::target::pin_out( hwlib::target::pins::d32 );

	NRF24 radio;
	uint8_t dataToTransmit[5] = {0, 0, 0, 0, 0};
	const uint8_t amountOfDataToTransmit = 5;
public:
	exchangeGameData(runGame * game, hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBus, const long long int duration);

	virtual void dataReceived(const uint8_t data[], const int len) override;

	void updateScore(const uint8_t playerNumber, const uint8_t dealtDamage);

};



#endif //__EXCHANGER_HPP