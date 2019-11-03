#include "exchanger.hpp"

exchangeGameData::exchangeGameData(runGame & game, hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBus, const long long int duration):
	game(game),
	radio(NRF24(spiBus, ce, csn, duration, 200))
{
	radio.addListener(this);
}