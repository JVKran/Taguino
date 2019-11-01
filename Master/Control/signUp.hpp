#ifndef __SIGNUP_HPP
#define __SIGNUP_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "playerData.hpp"
#include "rotaryEncoder.hpp"
#include "keypad.hpp"
#include "display.hpp"
#include "NRF24L01Control.hpp"

enum keypadID = {};
enum rotaryID = { LEFT, RIGHT, BUTTON };

class signUp : public rtos::task<>{
private:
	enum state_t { IDLE, ADDPLAYER};

	rtos::channel signUpChannel

	playerData& player;
	NRF24L01Control& nrf;
	display& oled;
	rotaryEncoder& encoder;
	keypad& key;


public:

	signUp();

	void keyPressed();
	void encoderPressed();
	void encoderTurnedToPos(int pos);
	void createPlayer();
	void main();

};

#endif //__SIGNUP_HPP