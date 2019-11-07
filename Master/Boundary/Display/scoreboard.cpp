/// @file

#include "scoreboard.hpp"

/// \brief
/// Constructor
/// \details
/// This class sets all elements in the arrays to zero.
scoreboard::scoreboard(){
    for(auto & element : playerNumbers){
        element = 0;

    }
    for(auto & element : playerScores){
        element = 0;
    }
	hwlib::cout << "Playernumber\t\t\tScore" << hwlib::endl;
    
	for(int i=0; i<32; i++){
        for(int j=0; j<8; j++){
            playerNames[i][j]='0';
        }
    }
}
void scoreboard::setName(uint8_t pos,std::array<char,8> naam, int len ){
    for(int i=0; i<len; i++){
    playerNames[pos][i]=naam[i];
    }
}
/// \brief
/// Update Scoreboard
/// \details
/// This function has one parameter; the data received by the NRF24L01+ chip.
/// Based on that the score and player are inserted and / or sorted.
void scoreboard::updateScoreBoard(const uint8_t data[5]){
    bool insert=true;
    for(int j = 0; j < 32; j++){
        if(playerNumbers[j] == data[1]){
            playerScores[j] += data[2];
            insert=false;
            break;
        }
    }

    if(insert == true){
        for(int j = 0; j < 32; j++){
            if(playerNumbers[j] == 0){
                playerNumbers[j]= data[1];
                playerScores[j] = data[2];
                insert=false;
                break;
            }
        }
    }

    bubbleSort(playerNumbers, playerScores,31);
}

/// \brief
/// Print Scoreboard
/// \details
/// This function prints the scoreboard to the display.
void scoreboard::printScoreboard(){
	hwlib::cout << "Playernumber\t\t\tScore" << hwlib::endl;
    
	for(int i=0; i<32; i++){
        for(const auto & element : playerNames[i]){
            if(element != '0'){
                hwlib::cout << char(element);
            } else {
                break;
            }
        }
        hwlib::cout << "\t\t\t" << playerScores[i] << hwlib::endl;
	}
}
