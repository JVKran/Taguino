/// @file

#ifndef __GAME_HPP
#define __GAME_HPP

#include "NRF24.hpp"
#include "entities.hpp"
#include "display.hpp"
#include "applicationLogic.hpp"
#include "scoreboard.hpp"


/// \brief
/// Game 
/// \details
/// Responsible for starting, and initializing of game.
class game : public radioListener, rtos::task<>{
private:
  	display & Display;
	NRF24 & radio;



	rtos::clock secondClock;                           //Activates main() every second to substract 1 from remainingTime.
  	int gameSeconds= 40;                                   //After initialization remainingSeconds and gameSeconds are equal.
  	int remainingSeconds =40;
  	rtos::timer updateClockTimer;


	int amountOfDataToTransmit = 5;
	uint8_t dataToTransmit[5];

	uint8_t receiveAddress[5] = {0, 0, 0, 0, 0};
	uint8_t transmitAddress[5] = {0, 0, 0, 0, 0};

	uint8_t assignedWeapons = 1;
	scoreboard board;

public:
	void setgametime(int time);
	uint8_t getGameTime();
	bool gamestarted =0;
	game(display & Display, NRF24 & radio,scoreboard & board);
	virtual void dataReceived(const uint8_t data[10], const int len) override;
	void main() override;
};

#endif //__GAME_HPP