#include "game.hpp"

game::game(NRF24 & radio):
	radio(radio)
{}

void game::dataReceived(const uint8_t data[], const int len){
	if(data[0] == 2){
		hwlib::cout << "Player " << data[1] << " dealt " << data[2] << " damage!" << hwlib::endl;

		radio.powerDown_rx();
		dataToTransmit[0] = data[1];					//2 is defined as newScoreMessage
		dataToTransmit[1] = data[2];
		for(const auto & element : onlineWeapons){
			transmitAddress[4] = element;
			radio.write_pipe( transmitAddress );				//Master address = 0x00
			radio.write( dataToTransmit, amountOfDataToTransmit );
		}
		radio.read_pipe(receiveAddress);
		radio.powerUp_rx();
	}
}