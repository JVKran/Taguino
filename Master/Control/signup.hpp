#ifndef __SIGNUP_HPP
#define __SIGNUP_HPP

#include "NRF24.hpp"
#include "keypad.hpp"
#include "input.hpp"

class signUp : public radioListener, public keypadListener  {
private:
	NRF24 radio;

	uint8_t assignedWeapons = 1;


	uint8_t transmitAddress[5] = {0, 0, 0, 0, 0};
	uint8_t receiveAddress[5] = {0, 0, 0, 0, 0};
	int amountOfDataToTransmit = 5;
	uint8_t dataToTransmit[5];
	T9Keys toetsenbord;
	//inputHandler handler;
public:
	signUp(NRF24 & radio, inputHandler &handler);

	void startGame(const uint8_t gameTime);
	virtual void dataReceived(const uint8_t data[], const int len) override;
	virtual void keyPressed(char karakter) override;
};

#endif //__SIGNUP_HPP


