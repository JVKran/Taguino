/// @file

#include "scoreboard.hpp"

/// \brief
/// Constructor
/// \details
/// This class sets all elements in the arrays to zero.
scoreboard::scoreboard(hwlib::terminal & scoreTerminal):
	scoreTerminal(scoreTerminal)
{
    for(auto & element : playerNumbers){
        element = 0;
    }
    for(auto & element : playerScores){
        element = 0;
    }
}

/// \brief
/// Update Scoreboard
/// \details
/// This function has one parameter; the data received by the NRF24L01+ chip.
/// Based on that the score and player are inserted and / or sorted.
void scoreboard::updateScoreBoard(uint8_t data[5]){
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
    scoreTerminal
    << '\f' << hwlib::left <<hwlib::setw(10) << int(playerNumbers[30])<<int(playerScores[30])<<'\n'<<
    hwlib::left << hwlib::setw(10) << int(playerNumbers[29])<<int(playerScores[29])<<'\n'<<
    hwlib::left << hwlib::setw(10) << int(playerNumbers[28])<<int(playerScores[28])<<'\n'<<
    hwlib::left << hwlib::setw(10) << int(playerNumbers[27])<<int(playerScores[27])<<'\n'<<
    hwlib::left << hwlib::setw(10) << int(playerNumbers[26])<<int(playerScores[26])<<'\n'<<
    hwlib::left << hwlib::setw(10) << int(playerNumbers[25])<<int(playerScores[25])<<'\n'<<
    hwlib::left << hwlib::setw(10) << int(playerNumbers[24])<<int(playerScores[24])<<'\n'<<
    hwlib::left << hwlib::setw(10) << int(playerNumbers[23])<<int(playerScores[23])<<'\n'<<
    hwlib::flush;
}
