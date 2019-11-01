#include "hwlib.hpp"
#include "rtos.hpp"
#include "playerData.hpp"
#include "rotaryEncoder.hpp"
#include "keypad.hpp"
#include "display.hpp"

enum keypadID = {};

class runGame : public rtos::task<>{
private:
	enum state_t {};

	rtos::channel toetsChannel;
	rtos::channel receiveMessageChannel;

	std::aray<playerData, 32> players = {};
	display& oled;
	rotaryEncoder& encoder;
	keypad& key;

public:

	runGame();

	void damageDone(uint8_t damage);
	void keyPressed();
	void encoderPressed();
	void encoderTurnedToPos(int pos);
	void startGame();
	void addPlayer();
	void decodeMessage();
	void main();

}