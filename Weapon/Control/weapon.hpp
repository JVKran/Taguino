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
		button triggerReleaseButton;
		button autoButton;
		button burstButton;
		button leftManualButton;
		button rightManualButton;
		inputHandler handler;
		bool triggerPressed = false;

		transmitter irTransmitter = transmitter();
		uint16_t dataToSend;
		hwlib::target::pin_out irReceiverGatePin = hwlib::target::pin_out(hwlib::target::pins::d30);

		runGame & game;
		const playerData & player;

		bool autoFireMode = false;

		bool burstFireMode = false;
		int shotBullets = 0;

		bool manualFireMode = true;

		hwlib::target::pin_in echoPin = hwlib::target::pin_in(hwlib::target::pins::d9);
		hwlib::target::pin_out triggerPin = hwlib::target::pin_out(hwlib::target::pins::d8);

		HCSR04 distanceSensor = HCSR04(triggerPin, echoPin);
		uint_fast64_t lastShot = 0;
		int measuredDistance = 0;

		weaponData weapon = weaponData(1, 2, 17);
		rtos::timer shootTimer;

		char readButton;
		rtos::channel<char, 5> buttonsChannel;
	public:
		weaponManager(display & Display, inputHandler & handler, runGame & game, playerData & player);

		virtual void buttonPressed(const char id) override;

		void newWeaponSelected(const int id);
		void shootBullet();

		void main() override;
};

#endif //__WEAPON_HPP