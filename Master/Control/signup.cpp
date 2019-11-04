#include "signup.hpp"

signUp::signUp(NRF24 & radio):
	radio(radio)
{
	for(auto & element : onlineWeapons){
		element = 0;
	}
}

void signUp::dataReceived(const uint8_t data[], const int len){
	if(data[0] == 1){
		for(uint8_t i = 0; i < 32; i++){
			if(onlineWeapons[i] == 0){
				onlineWeapons[i] = data[1];
				hwlib::cout << "Weapon turned on. Gave him address " << hwlib::endl;
				radio.powerDown_rx();
				transmitAddress[4] = 100;
				radio.write_pipe( transmitAddress );
				dataToTransmit[0] = 8;					//2 is defined as newScoreMessage
				dataToTransmit[1] = i;
				hwlib::cout << i << "." << hwlib::endl;
				radio.write( dataToTransmit, amountOfDataToTransmit );
				radio.read_pipe(receiveAddress);
				radio.powerUp_rx();
				break;
			}
		}
	}
}