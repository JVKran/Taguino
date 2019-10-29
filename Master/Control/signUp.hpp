#include "hwlib.hpp"
#include "rtos.hpp"

enum keypadID = {};

class signUp : public rtos::task<> {
private:
	enum state_t	= {};

	rtos::channel signUpChannel;

	PlayerData& player;
	Display& oled;
	RotaryEncoder& encoder;
	Keypad& keypad;

public:
	signUp();

	void getPlayerData();
	void setPlayerData();
	void draw();
	void keyPressed();
	void encoderPressed();
	void encoderTurnedToPos();

}