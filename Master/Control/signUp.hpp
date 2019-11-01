#ifndef __SIGNUP_HPP
#define __SIGNUP_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "playerData.hpp"
#include "rotaryEncoder.hpp"
#include "keypad.hpp"
#include "display.hpp"
#include "NRF24L01Control.hpp"

// this file contains Doxygen lines
/// @file

/// \brief
/// control object to sign up
/// \details
/// This object can be used to add a player to runGame

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


	/// \brief
    /// constructor
    /// \details
    /// Creates a object of signUp
	signUp();

	/// \brief
    /// check if key pressed
    /// \details
    /// With this function you are able to read if a key has been pressed
	void keyPressed();

	/// \brief
    /// encoder pressed
    /// \details
    /// With this function you are able to read if the encoder button has been 
    /// pressed
	void encoderPressed();

	/// \brief
    /// check direction
    /// \details
    /// With this function you are able to read if the encoder has been turned
    /// to left or right
	void encoderTurnedToPos(int pos);

	/// \brief
    /// create a player
    /// \details
    /// With this function you are able to create a player
	void createPlayer();

	/// \brief
    /// main
    /// \details
    /// The main
	void main();

};

#endif //__SIGNUP_HPP