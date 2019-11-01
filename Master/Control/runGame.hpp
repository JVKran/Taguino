#include "hwlib.hpp"
#include "rtos.hpp"
#include "playerData.hpp"
#include "rotaryEncoder.hpp"
#include "keypad.hpp"
#include "display.hpp"

enum keypadID = {};
enum rotaryID = { LEFT, RIGHT, BUTTON };

class runGame : public rtos::task<>{
private:
	enum state_t {};

	rtos::channel 	toetsChannel;
	rtos::channel 	receiveMessageChannel;
	rtos::pool		newPlayerPool;
	rtos::flag		newPlayerFlag;

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