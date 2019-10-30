#ifndef __GAME_HPP
#define __GAME_HPP

#include "entities.hpp"
#include "transceiver.hpp"
#include "RGBLed.hpp"
#include "rtos.hpp"

class runGame : public receiverListener, public rtos::task<> {
	private:
		playerData player;

    	RGBLed Led = RGBLed();

    	hwlib::target::pin_in irReceiverPin = hwlib::target::pin_in(hwlib::target::pins::d5);
  		receiver irReceiver = receiver(irReceiverPin, this);

  		rtos::clock secondClock;
  		rtos::channel<uint16_t, 10> receivedDataChannel;
	public:
		runGame(const playerData & player);
		playerData getPlayerData();

		virtual void dataReceived(const uint16_t data);

		void main() override;
};


#endif //__GAME_HPP