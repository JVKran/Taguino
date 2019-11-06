#include "scoreboard.hpp"

scoreboard::scoreboard(hwlib::terminal & scoreTerminal):
	scoreTerminal(scoreTerminal)
{HWLIB_TRACE;}

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
	scoreTerminal<<"Scoreboard";
    scoreTerminal<<"Player\tScore\n" << 
        "\t0002" <<int(playerNumbers[29])<<"\t" <<int(playerScores[29])<<
        "\t0003" <<int(playerNumbers[28])<<"\t" <<int(playerScores[28])<<
        "\t0004" <<int(playerNumbers[27])<<"\t" <<int(playerScores[27])<<
        "\t0005" <<int(playerNumbers[26])<<"\t" <<int(playerScores[26])<<
        "\t0005" <<int(playerNumbers[25])<<"\t" <<int(playerScores[25])<<hwlib::flush;
}