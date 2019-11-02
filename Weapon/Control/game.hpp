#ifndef __GAME_HPP
#define __GAME_HPP

#include "entities.hpp"
#include "receiver.hpp"
#include "RGBLed.hpp"
#include "display.hpp"
#include "rtos.hpp"

class runGame : public messageListener, public rtos::task<> {
private:
	display & Display;
	playerData player;

    RGBLed Led = RGBLed();

  	uint16_t receivedData;

  	weaponSettings weaponStats = weaponSettings();

  	rtos::clock secondClock;                           //Activates main() every second to substract 1 from remainingTime.
  	int gameSeconds;                                   //After initialization remainingSeconds and gameSeconds are equal.
  	int remainingSeconds;

  	rtos::channel<uint16_t, 10> receivedDataChannel;   //Contains received Infrared Messages.
  	rtos::timer updateClockTimer;
public:
	runGame(display & Display, const playerData & player, const int playSeconds);
	
	playerData getPlayerData();                         //Used by weaponManager to get playerNumber for infraredMessage.

	virtual void messageReceived(const uint16_t data);

	void main() override;
};


#endif //__GAME_HPP