#ifndef __GAME_HPP
#define __GAME_HPP

#include "entities.hpp"
#include "transceiver.hpp"
#include "RGBLed.hpp"
#include "display.hpp"
#include "rtos.hpp"

class runGame : public receiverListener, public rtos::task<> {
	private:
		display & Display;
		playerData player;

    	RGBLed Led = RGBLed();

    	hwlib::target::pin_in irReceiverPin = hwlib::target::pin_in(hwlib::target::pins::d5);
  		receiver irReceiver;;
  		uint16_t receivedData;

  		rtos::clock secondClock;
  		int gameSeconds;
  		int remainingSeconds;
  		rtos::channel<uint16_t, 10> receivedDataChannel;
  		rtos::timer updateClockTimer;
	public:
		runGame(display & Display, const playerData & player, const int playSeconds, const long long int duration = 1000);
		playerData getPlayerData();

		virtual void dataReceived(const uint16_t data);

		void main() override;
};


#endif //__GAME_HPP