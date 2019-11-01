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
/// control object to run the game
/// \details
/// This object can be used to change the scoreboard, send messages to 
///players and add a player to the list 

enum keypadID = {};
enum rotaryID = { LEFT, RIGHT, BUTTON };

class runGame : public rtos::task<>{
private:
	enum state_t { IDLE, NEWMESSAGE, ADDPLAYER, CHANGESCOREBOARD, SENDMESSAGE };

	rtos::channel 	toetsChannel;
	rtos::channel 	receiveMessageChannel;
	rtos::pool		newPlayerPool;
	rtos::flag		newPlayerFlag;

	std::aray<playerData, 32> players = {};
	NRF24L01Control& nrf;
	display& oled;
	rotaryEncoder& encoder;
	keypad& key;

public:

	/// \brief
    /// constructor
    /// \details
    /// This constructor does initialize the values display, rotaryEncoder and keypad
	runGame( display& o, NRF24L01Control& nrf, rotaryEncoder& re, keypad& kp );

	/// \brief
    /// get the name
    /// \details
    /// This function will edit the scoreboard depending on what you give it
	void changeScoreboard();

	/// \brief
    /// get the name
    /// \details
    /// With this function you are able to read which key has been pressed
	void keyPressed();

	/// \brief
    /// get the name
    /// \details
    /// With this function you are able to read the if the encoder button has been pressed
	void encoderPressed();

	/// \brief
    /// get the name
    /// \details
    /// With this function you are able to read if the encoder is turning left or right
	void encoderTurnedToPos(int pos);

	/// \brief
    /// get the name
    /// \details
    /// With this function you are able to start the game
	void startGame();

	/// \brief
    /// get the name
    /// \details
    /// With this function you are able to add a player in game
	void addPlayer();

	/// \brief
    /// get the name
    /// \details
    /// With this function you are able to read what is send in the message
	void decodeMessage();

	/// \brief
    /// get the name
    /// \details
    /// The main
	void main();

}