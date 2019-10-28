#ifndef __WEAPON_HPP
#define __WEAPON_HPP

#include "input.hpp"
#include "entities.hpp"
#include "HCSR04.hpp"
#include "rtos.hpp"
#include "game.hpp"

class weaponManager : public buttonListener, public rtos::task<> {
	private:
		button triggerButton;
		button autoButton;
		button manualButton;
		inputHandler handler;

		runGame & game;
		const playerData & player;

		hwlib::target::pin_in echoPin = hwlib::target::pin_in(hwlib::target::pins::d9);
		hwlib::target::pin_out triggerPin = hwlib::target::pin_out(hwlib::target::pins::d8);
		HCSR04 distanceSensor = HCSR04(triggerPin, echoPin);

		weaponData weapon = weaponData(0);

		char readButton;
		rtos::channel<char, 5> buttonsChannel;
	public:
		weaponManager(inputHandler & handler, runGame & game);

		virtual void buttonPressed(const char id) override;

		void main() override;
};

#endif //__WEAPON_HPP