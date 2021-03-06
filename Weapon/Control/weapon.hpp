/// @file

#ifndef __WEAPON_HPP
#define __WEAPON_HPP

#include "input.hpp"
#include "entities.hpp"
#include "display.hpp"
#include "HCSR04.hpp"
#include "rtos.hpp"
#include "game.hpp"
#include "transmitter.hpp"


/// \brief
/// Weapon Manager
/// \details
/// This class is responsible for managing the weapon; bullets, magazines, weapons and fireModes.
class weaponManager : public buttonListener, public rtos::task<> {
	private:
		display & Display;
		button triggerButton;
		button triggerReleaseButton;
		button autoButton;
		button burstButton;
		button leftManualButton;
		button rightManualButton;
		inputHandler & handler;
		bool triggerPressed = false;

		infraredTransmitter & irTransmitter;
		uint16_t dataToSend;
		
		playerData & player;

		bool autoFireMode = false;

		bool burstFireMode = false;
		int shotBullets = 0;

		bool manualFireMode = true;

		hwlib::target::pin_in echoPin = hwlib::target::pin_in(hwlib::target::pins::d9);
		hwlib::target::pin_out triggerPin = hwlib::target::pin_out(hwlib::target::pins::d8);

		HCSR04 distanceSensor = HCSR04(triggerPin, echoPin);
		uint_fast64_t lastShot = 0;
		int measuredDistance = 0;

		weaponData weapon = weaponData(0, 2, 4);
		weaponSettings settings = weaponSettings();
		rtos::timer shootTimer;

		char readButton;
		rtos::channel<char, 5> buttonsChannel;

		rtos::flag newWeaponFlag;
		rtos::pool<int> newWeaponPool;
		int weaponId;
	public:
		weaponManager(display & Display, inputHandler & handler, playerData & player,  infraredTransmitter & irTransmitter);
		virtual void buttonPressed(const char id) override;

		void newWeaponSelected(const int id);
		void selectNewWeapon();

		void shootBullet();

		void main() override;
};

#endif //__WEAPON_HPP