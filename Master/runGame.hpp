#include <iostream>

class runGame : public rtos::task<>{
private:
	rtos::channel toetsChannel;
	rtos::channel receiveMessageChannel;

	std::array<playerData, 32> players = {};

}
