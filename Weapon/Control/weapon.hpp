#ifndef __WEAPON_HPP
#define __WEAPON_HPP

#include "input.hpp"
#include "entities.hpp"
#include "display.hpp"
#include "HCSR04.hpp"
#include "rtos.hpp"
#include "game.hpp"
#include "transceiver.hpp"

class weaponManager : public buttonListener, public rtos::task<> {
	private:
		display & Display;
		button triggerButton;
		button autoButton;
		button manualButton;
		inputHandler handler;

		transmitter irTransmitter = transmitter();
		uint16_t dataToSend;

		runGame & game;
		const playerData & player;

		hwlib::target::pin_in echoPin = hwlib::target::pin_in(hwlib::target::pins::d9);
		hwlib::target::pin_out triggerPin = hwlib::target::pin_out(hwlib::target::pins::d8);

		HCSR04 distanceSensor = HCSR04(triggerPin, echoPin);
		uint_fast64_t lastShot;
		int measuredDistance = 0;

		weaponData weapon = weaponData(0);

		char readButton;
		rtos::channel<char, 5> buttonsChannel;
	public:
		weaponManager(display & Display, inputHandler & handler, runGame & game);

		virtual void buttonPressed(const char id) override;

		void main() override;
};

#endif //__WEAPON_HPP