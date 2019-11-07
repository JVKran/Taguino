/// @file

#include "scoreboard.hpp"

/// \brief
/// Constructor
/// \details
/// This class sets all elements in the arrays to zero.
scoreboard::scoreboard(hwlib::terminal & scoreTerminal):
	scoreTerminal(scoreTerminal)
{
    for(auto element : playerNumbers){
        element = 0;
    }
    for(auto element : playerScores){
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
}

/// \brief
/// Print Scoreboard
/// \details
/// This function prints the scoreboard to the display.
void scoreboard::printScoreboard(){
    hwlib::cout<<int(playerNumbers[0])<<hwlib::endl;
    hwlib::cout<<int(playerNumbers[1])<<hwlib::endl;
    hwlib::cout<<int(playerNumbers[2])<<hwlib::endl;
    hwlib::cout<<int(playerNumbers[3])<<hwlib::endl;
    hwlib::cout<<int(playerNumbers[4])<<hwlib::endl;

    scoreTerminal <<
    int(playerNumbers[0])<<'\t'<<int(playerNumbers[0])<<'\n'<<
    int(playerNumbers[1])<<'\t'<<int(playerNumbers[1])<<'\n'<<
    int(playerNumbers[2])<<'\t'<<int(playerNumbers[2])<<'\n'<<
    int(playerNumbers[3])<<'\t'<<int(playerNumbers[3])<<'\n'<<
    int(playerNumbers[4])<<'\t'<<int(playerNumbers[4])<<'\n'<<
    hwlib::flush;
}
