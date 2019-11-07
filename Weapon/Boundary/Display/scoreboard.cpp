#include "scoreboard.hpp"

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

void scoreboard::printScoreboard(){

    scoreTerminal
    << hwlib::left <<hwlib::setw(10) << int(playerNumbers[0])<<int(playerScores[0])<<'\n'<<
    hwlib::left << hwlib::setw(10) << int(playerNumbers[1])<<int(playerScores[1])<<'\n'<<
    hwlib::left << hwlib::setw(10) << int(playerNumbers[2])<<int(playerScores[2])<<'\n'<<
    hwlib::left << hwlib::setw(10) << int(playerNumbers[3])<<int(playerScores[3])<<'\n'<<
    hwlib::left << hwlib::setw(10) << int(playerNumbers[4])<<int(playerScores[4])<<'\n'<<
    hwlib::left << hwlib::setw(10) << int(playerNumbers[5])<<int(playerScores[5])<<'\n'<<
    hwlib::left << hwlib::setw(10) << int(playerNumbers[6])<<int(playerScores[6])<<'\n'<<
    hwlib::left << hwlib::setw(10) << int(playerNumbers[7])<<int(playerScores[7])<<'\n'<<
    hwlib::flush;
}