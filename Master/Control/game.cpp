/// @file

#include "game.hpp"

/// \brief
/// Constructor
/// \details
/// Starts Game for all online weapons based on protocol as defined in documentation.
game::game(display & Display, NRF24 & radio, scoreboard &board):
	task(1,"gamerunning"),
	Display(Display),
	radio(radio),
	secondClock(this, 1'000'000, "Second Clock for time keeping"),
	updateClockTimer(this, "update Clock Timer"),
	board(board)
{}

/// \brief
/// SetGameTime
/// \details
/// This function sets the time attributes.
void game::setgametime(int time){
  	gameSeconds= time;                                   
  	remainingSeconds =time;
}

/// \brief
/// getGameTime
/// \details
/// This function gets the remaining gameSeconds;
uint8_t game::getGameTime(){
	return gameSeconds;
}

/// \brief
/// DataReceived
/// \details
/// This function gets called when data is received with parameters data and len. Based on protocol
/// as written in documentation things are done.
void game::dataReceived(const uint8_t data[10], const int len){
	if(data[0] == 2){
		hwlib::cout << "Player " << data[1] << " dealt " << int(data[2]) << " damage!" << hwlib::endl;
		//board.playerScores[data[1]]=data[2];
		board.updateScoreBoard(data);
		board.printScoreboard();

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
	} else if(data[0] == 1){
		assignedWeapons++;
		if(assignedWeapons > 31){
			assignedWeapons = 31;
		}
	}
}

void game::main(){
	Display.showTime(remainingSeconds);							
	updateClockTimer.set((gameSeconds / 100 )* 1'000'000);
	for(;;){

		auto event= wait(secondClock/*+updateClockTimer*/);

		if ((event == secondClock)&&(gamestarted)) {
			//HWLIB_TRACE;
			remainingSeconds--;
			Display.showTime(remainingSeconds);				
		}
	}
}