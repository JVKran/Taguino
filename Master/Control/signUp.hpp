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


public:

}