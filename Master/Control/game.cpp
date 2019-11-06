#include "game.hpp"

game::game(NRF24 & radio):
	radio(radio)
{}

void game::swap(uint8_t *xp, uint8_t *yp){  
	uint8_t temp = *xp;  
	*xp = *yp;  
	*yp = temp;  
}  

void game::bubbleSort(std::array<uint8_t, 32> scores, std::array<uint8_t, 32> numbers, int n){  
    int i, j;  
    for (i = 0; i < n-1; i++){
      	for (j = 0; j < n-i-1; j++){
      		if (scores[j] < scores[j+1]){
              	swap(&scores[j], &scores[j+1]); 
              	swap(&numbers[j], &numbers[j+1]);
      		}
      	}  
    }
}

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
		for(int i = 0; i < 31; i++){
			hwlib::cout << board.playerNumbers[i] << "\t\t\t" << board.playerScores[i] << hwlib::endl;
		}
	} else if(data[0] == 1){
		assignedWeapons++;
		if(assignedWeapons > 31){
			assignedWeapons = 31;
		}
	}
}