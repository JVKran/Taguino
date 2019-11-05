#ifndef __SIGNUP_HPP
#define __SIGNUP_HPP

#include "NRF24.hpp"

class signUp : public radioListener {
private:
	NRF24 radio;

	uint8_t assignedWeapons = 1;


	uint8_t transmitAddress[5] = {0, 0, 0, 0, 0};
	uint8_t receiveAddress[5] = {0, 0, 0, 0, 0};
	int amountOfDataToTransmit = 5;
	uint8_t dataToTransmit[5];
public:
	signUp(NRF24 & radio);

	void startGame(const uint8_t gameTime);
	virtual void dataReceived(const uint8_t data[], const int len) override;
};

#endif //__SIGNUP_HPP


