#include "scoreboard.hpp"

/*
scoreboard::scoreboard(hwlib::window & window, hwlib::glcd_oled & oled, std::array<playerData, 5> players):
	window(window),
	oled(oled),
	players(players)
{
	// auto windowFont 			= hwlib::font_default_8x8();
	// auto windowName 			= hwlib::window_part(window, hwlib::xy(114, 3), hwlib::xy(122, 12));
	// auto windowNameTerminal 	= hwlib::terminal_from(windowName, windowFont);
	// hwlib::circle nameCircle	= hwlib::circle(hwlib::xy(117, 6), 5);

	// auto windowPartFirstPlace 	= hwlib::window_part(window, hwlib::xy(0,10), hwlib::xy(124, 20));
	// auto windowPartSecondPlace 	= hwlib::window_part(window, hwlib::xy(0,21), hwlib::xy(124, 31));
	// auto windowPartThirdPlace 	= hwlib::window_part(window, hwlib::xy(0,32), hwlib::xy(124, 42));
	// auto windowPartFourthPlace 	= hwlib::window_part(window, hwlib::xy(0,43), hwlib::xy(124, 53));
	// auto windowPartFifthPlace 	= hwlib::window_part(window, hwlib::xy(0,54), hwlib::xy(124, 64));

	// auto terminalFirstPlace 	= hwlib::terminal_from(windowPartFirstPlace, windowFont);
	// auto terminalSecondPlace 	= hwlib::terminal_from(windowPartSecondPlace, windowFont);
	// auto terminalThirdPlace 	= hwlib::terminal_from(windowPartThirdPlace, windowFont);
	// auto terminalFourthPlace 	= hwlib::terminal_from(windowPartFourthPlace, windowFont);
	// auto terminalFifthPlace 	= hwlib::terminal_from(windowPartFifthPlace, windowFont);

	// terminalFirstPlace 	<< hwlib::left <<hwlib::setw(11) << players[0].getName() << players[0].getScore();
	// terminalSecondPlace << hwlib::left <<hwlib::setw(11) << players[1].getName() << players[1].getScore();
	// terminalThirdPlace 	<< hwlib::left <<hwlib::setw(11) << players[2].getName() << players[2].getScore();
	// terminalFourthPlace << hwlib::left <<hwlib::setw(11) << players[3].getName() << players[3].getScore();
	// terminalFifthPlace 	<< hwlib::left <<hwlib::setw(11) << players[4].getName() << players[4].getScore();
	
	// windowNameTerminal 	<< 'B';
	// windowNameTerminal.flush();
	// nameCircle.draw(oled);
}
*/
#include "scoreboard.hpp"

scoreboard::scoreboard()

{
    for(auto & element : playerNumbers){
        element = 0;

    }
    for(auto & element : playerScores){
        element = 0;
    }
}

void scoreboard::updateScoreBoard(const uint8_t data[5]){
    bool insert=true;
    for(int j = 0; j < 32; j++){
		//hwlib::cout<<"data "<<data[1]<<"   "<<j<<"   "<<data[2]<<hwlib::endl;
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
	hwlib::cout << "Playernumber\t\t\tScore" << hwlib::endl;

	for(int i=0; i<32; i++){
hwlib::cout << playerNumbers[i] << "\t\t\t" << playerScores[i] << hwlib::endl;
    // hwlib::cout<<int(playerNumbers[1])<<hwlib::endl;
    // hwlib::cout<<int(playerNumbers[2])<<hwlib::endl;
    // hwlib::cout<<int(playerNumbers[3])<<hwlib::endl;
    // hwlib::cout<<int(playerNumbers[4])<<hwlib::endl;
	}
    // scoreTerminal <<
    // int(playerNumbers[0])<<'\t'<<int(playerNumbers[0])<<'\n'<<
    // int(playerNumbers[1])<<'\t'<<int(playerNumbers[1])<<'\n'<<
    // int(playerNumbers[2])<<'\t'<<int(playerNumbers[2])<<'\n'<<
    // int(playerNumbers[3])<<'\t'<<int(playerNumbers[3])<<'\n'<<
    // int(playerNumbers[4])<<'\t'<<int(playerNumbers[4])<<'\n'<<
    // hwlib::flush;
}