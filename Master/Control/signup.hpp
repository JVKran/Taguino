/// @file

#ifndef __SIGNUP_HPP
#define __SIGNUP_HPP

#include "NRF24.hpp"
#include "keypad.hpp"
#include "input.hpp"
#include "mp3.hpp"

#include "game.hpp"


/// \brief
/// Sign Up
/// \details
/// This class is responsible for signing up. Therfore it has a keypad and radio.
class signUp : public radioListener, public keypadListener  {


private:
	NRF24 radio;

	uint8_t assignedWeapons = 1;


	uint8_t transmitAddress[5] = {0, 0, 0, 0, 0};
	uint8_t receiveAddress[5] = {0, 0, 0, 0, 0};
	int amountOfDataToTransmit = 5;
	uint8_t dataToTransmit[5];
	T9Keys toetsenbord;
	mp3Control<2> mp3Player = mp3Control<2>(); 
	//inputHandler handler;
	game & Game;

public:
	signUp(NRF24 & radio, inputHandler &handler, game &Game);

	void startGame(const uint8_t gameTime);
	virtual void dataReceived(const uint8_t data[], const int len) override;
	virtual void keyPressed(char karakter) override;
};

#endif //__SIGNUP_HPP


