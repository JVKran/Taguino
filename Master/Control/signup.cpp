#include "signup.hpp"


// Lobby muziek in constructor en in start game actie
signUp::signUp(NRF24 & radio, inputHandler &handler):
	radio(radio),
	toetsenbord(this)

	{
		mp3Player.startPlayingSound(1); // Start lobby music once.
		handler.addkeypad(&toetsenbord);
	}

void signUp::dataReceived(const uint8_t data[10], const int len){
	if(data[0] == 1){
		if(assignedWeapons < 31){
			hwlib::cout << "Weapon turned on. Gave him address " << hwlib::endl;
			radio.powerDown_rx();
			transmitAddress[4] = 100;
			radio.write_pipe( transmitAddress );
			dataToTransmit[0] = 8;					//2 is defined as newScoreMessage
			dataToTransmit[1] = assignedWeapons;
			hwlib::cout << assignedWeapons << "." << hwlib::endl;
			radio.write( dataToTransmit, amountOfDataToTransmit );
			radio.read_pipe(receiveAddress);
			radio.powerUp_rx();
			assignedWeapons++;
		}
	}
}
void signUp::keyPressed(char karakter){
			//HWLIB_TRACE;

	hwlib::cout<<karakter<<hwlib::endl;

}

void signUp::startGame(const uint8_t gameTime){
	mp3Player.startPlayingSound(2);	// Start action music once.
	
	radio.powerDown_rx();
	hwlib::wait_ms(100);
	for(uint8_t i = 1; i < assignedWeapons; i++){
		transmitAddress[4] = i;
		radio.write_pipe( transmitAddress );
		dataToTransmit[0] = 1;					//2 is defined as newScoreMessage
		dataToTransmit[1] = gameTime;
		hwlib::cout << "Started game for player " << i << "!" << hwlib::endl;
		radio.write( dataToTransmit, amountOfDataToTransmit );
	}
	radio.read_pipe(receiveAddress);
	radio.powerUp_rx();
}