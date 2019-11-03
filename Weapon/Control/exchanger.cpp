#include "exchanger.hpp"

exchangeGameData::exchangeGameData(runGame * game, hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBus, const long long int duration):
	game(game),
	radio(NRF24(spiBus, ce, csn, duration, game->getPlayerData().getPlayerNumber()))
{
	radio.addListener(this);
}

void exchangeGameData::updateScore(const uint8_t playerNumber, const uint8_t dealtDamage){
	radio.write_pipe( 0x00 );				//Master address = 0x00
   	radio.powerDown_rx();

   	dataToTransmit[0] = playerNumber;
   	dataToTransmit[1] = dealtDamage;

	radio.write( dataToTransmit, amountOfDataToTransmit );
   	radio.read_pipe(game->getPlayerData().getPlayerNumber());
   	radio.powerUp_rx();
}

void exchangeGameData::dataReceived(const uint8_t data[], const int len){
	for(int i = 0; i < len; i++){
		hwlib::cout << data[i] << " ";
	}
	hwlib::cout << hwlib::endl;
	switch(data[0]){
		case 1:
			hwlib::cout << "Game started" << hwlib::endl;
			break;
		case 2:
			hwlib::cout << "Playernumber " << data[1] << " has a score of " << data[2] << " hence his position is " << data[3] << hwlib::endl;
			break;
		case 3:
			hwlib::cout << "InfiniteBullets Activated" << hwlib::endl;
			break;
		case 4:
			hwlib::cout << "InstaDeath Activated" << hwlib::endl;
			break;
		case 5:
			hwlib::cout << "Time to Play: " << data[1] << " out of " << data[2] << " seconds." << hwlib::endl;
			break;
		case 6:
			hwlib::cout << "PlayerNumber " << data[1] << " has name " << data[2] << data[3] << data[4] << hwlib::endl;
			break;
	}
}