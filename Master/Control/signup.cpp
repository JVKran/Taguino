/// @file

#include "signup.hpp"


/// \brief
/// Constructor
/// \details
/// Starts Lobby music to join game.
signUp::signUp(NRF24 & radio, inputHandler &handler, game &Game,scoreboard &board):
	radio(radio),
	toetsenbord(this),
	Game(Game),
	board(board)


	{
		mp3Player.startPlayingSound(1); // Start lobby music once.
		handler.addkeypad(&toetsenbord);
	}

/// \brief
/// Data Received
/// \details
/// Gets called when data is received
void signUp::dataReceived(const uint8_t data[10], const int len){
	if(data[0] == 1){
		if(assignedWeapons < 31){
			hwlib::cout << "Weapon turned on. Gave him address " << hwlib::endl;
			radio.powerDown_rx();
			transmitAddress[4] = 100;
			radio.write_pipe( transmitAddress );
			dataToTransmit[0] = 8;					//2 is defined as newScoreMessage
			dataToTransmit[1] = assignedWeapons;
				board.setName(assignedWeapons, name, namepos);
			hwlib::cout << assignedWeapons << "." << hwlib::endl;
			radio.write( dataToTransmit, amountOfDataToTransmit );
			radio.read_pipe(receiveAddress);
			radio.powerUp_rx();
			assignedWeapons++;
		}
		//hwlib::wait_ms(5000);
		//startGame(100);
	}
}

/// \brief
/// Key Pressed
/// \details
/// Gets called when a key is pressed.
void signUp::keyPressed(char karakter){
			//HWLIB_TRACE;

	name[namepos]= karakter;
	namepos++;
	for(int i=0; i<namepos; i++){
		hwlib::cout<<name[i];
	}
	


}

/// \brief
/// StartGame
/// \details
/// Starts Game for all online weapons based on protocol as defined in documentation.
void signUp::startGame(const uint8_t gameTime){
	HWLIB_TRACE;
	Game.gamestarted =1;
	mp3Player.startPlayingSound(2);	// Start action music once.
	
	radio.powerDown_rx();
	hwlib::wait_ms(1000);
	for(uint8_t i = 1; i < assignedWeapons; i++){
		transmitAddress[4] = i;
		radio.write_pipe( transmitAddress );
		dataToTransmit[0] = 1;					//2 is defined as newScoreMessage
		dataToTransmit[1] = Game.getGameTime();
		hwlib::cout << "Started game for player " << i << "!" << hwlib::endl;
		radio.write( dataToTransmit, amountOfDataToTransmit );
		hwlib::wait_ms(100);
		transmitAddress[4] = i;
		radio.write_pipe( transmitAddress );
		dataToTransmit[0] = 1;					//2 is defined as newScoreMessage
		dataToTransmit[1] = Game.getGameTime();
		hwlib::cout << "Started game for player " << i << "!" << hwlib::endl;
		radio.write( dataToTransmit, amountOfDataToTransmit );
		hwlib::wait_ms(100);
				transmitAddress[4] = i;
		radio.write_pipe( transmitAddress );
		dataToTransmit[0] = 1;					//2 is defined as newScoreMessage
		dataToTransmit[1] = Game.getGameTime();
		hwlib::cout << "Started game for player " << i << "!" << hwlib::endl;
		radio.write( dataToTransmit, amountOfDataToTransmit );
		hwlib::wait_ms(100);

	}
	radio.read_pipe(receiveAddress);
	radio.powerUp_rx();

}