#include "signup.hpp"

signUp::signUp(NRF24 & radio, inputHandler &handler):
	radio(radio),
	toetsenbord(this)

{handler.addkeypad(&toetsenbord);}

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
		hwlib::wait_ms(5000);
		startGame(100);
	}
}
void signUp::keyPressed(char karakter){
			//HWLIB_TRACE;

	hwlib::cout<<karakter<<hwlib::endl;

}
void signUp::sendName(char naam[], int len){
			hwlib::cout << "Weapon anamed. Gave him address " << hwlib::endl;
			radio.powerDown_rx();
			for(int i=1; i<assignedWeapons; i++){
			transmitAddress[4] = assignedWeapons-1;
			radio.write_pipe( transmitAddress );
			dataToTransmit[0] = 6;					//2 is defined as newScoreMessage
			dataToTransmit[1] = assignedWeapons;
			for(int i=0; i<len; i++){
				dataToTransmit[i+2]=naam[i];
			}
			hwlib::cout <<"naam aan"<< assignedWeapons << "." << hwlib::endl;
			radio.write( dataToTransmit, amountOfDataToTransmit );
			}
			radio.read_pipe(receiveAddress);
			radio.powerUp_rx();
	
}

void signUp::startGame(const uint8_t gameTime){
	radio.powerDown_rx();
	hwlib::wait_ms(100);
	char naam[4] ={'t','e','s','t'};
	for(uint8_t i = 1; i < assignedWeapons; i++){
		transmitAddress[4] = i;
		radio.write_pipe( transmitAddress );
		dataToTransmit[0] = 1;					//2 is defined as newScoreMessage
		dataToTransmit[1] = gameTime;
		hwlib::cout << "Started game for player " << i << "!" << hwlib::endl;
		radio.write( dataToTransmit, amountOfDataToTransmit );
	}
	sendName(naam,4);
	radio.read_pipe(receiveAddress);
	radio.powerUp_rx();
}