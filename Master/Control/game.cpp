#include "game.hpp"

game::game(NRF24 & radio):
	radio(radio)
{}

void game::dataReceived(const uint8_t data[10], const int len){
	if(data[0] == 2){
		hwlib::cout << "Player " << data[1] << " dealt " << int(data[2]) << " damage!" << hwlib::endl;

		radio.powerDown_rx();
		dataToTransmit[0] = 2;
		dataToTransmit[1] = data[1];					//2 is defined as newScoreMessage
		dataToTransmit[2] = data[2];
		for(uint8_t i = 0; i < assignedWeapons; i++){
			transmitAddress[4] = i;
			radio.write_pipe( transmitAddress );				//Master address = 0x00
			radio.write( dataToTransmit, amountOfDataToTransmit );
		}
		radio.read_pipe(receiveAddress);
		radio.powerUp_rx();
		for(int i = 0; i < 32; i++){
			if(board.playerNumbers[i] == data[1]){
				board.playerScores[i] += data[2];
				break;
			}
			if(i == 31){
				for(int i = 0; i < 32; i++){
					if(board.playerScores[i] < data[2]){
						for(int j = 32; j > i; j--){
							board.playerScores[j] = board.playerScores[j + 1];
							board.playerNumbers[j] = board.playerNumbers[j + 1];
						}
						board.playerScores[i] = data[2];
						board.playerNumbers[i] = data[1];
						break;
					}
				}
			}
		}
		bubbleSort(board.playerScores, board.playerNumbers, 31);
		hwlib::cout << "Playernumber\t\t\tScore" << hwlib::endl;
		for(int i = 24; i < 30; i++){
			hwlib::cout << board.playerNumbers[i] << "\t\t\t" << board.playerScores[i] << hwlib::endl;
		}
	}
}