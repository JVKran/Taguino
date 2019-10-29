#include "hwlib.hpp"
#include "rtos.hpp"

enum keypadID = {};

class runGame : public rtos::task<>{
private:
	enum state_t = {};

	rtos::channel toetsChannel;
	rtos::channel receiveMessageChannel;

	std::array<playerData, 32> players = {};
	rotaryEncoder& encoder;
	keypad& keypad;

public:
	runGame();

	void damageDone(uint8_t damage);
	void keyPressed();
	void encoderPressed();
	void encoderTurnedToPos(int pos);
	void startGame();
	void decodeMessage();
	void main();

}
