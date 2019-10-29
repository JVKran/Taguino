#include <iostream>

class runGame : public rtos::task<>{
private:
	rtos::channel toetsChannel;
	rtos::channel receiveMessageChannel;

	std::array<playerData, 32> players = {};
	rotaryEncoder& encoder;
	keypad& keypad;

public:
	runGame();

	void damageDone(uint8_t damage);
	bool keyPressed();
	bool encoderPressed();
	void encoderTurnedToPos(int pos);
	void startGame();
	void decodeMessage();
	void main();

}
