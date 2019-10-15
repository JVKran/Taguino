#ifndef __WEAPONMANAGER_HPP
#define __WEAPONMANAGER_HPP

#include "hwlib.hpp"
#include "display.hpp"
#include "weapon.hpp"
// #include "distanceSensor.hpp"
// #include "transmitInfraredMessage.hpp"
// #include "rotaryEncode.hpp"
// #include "button.hpp"

class weaponManager{
private:
	display & Display;
	weapon Weapon;
	// rotaryEncode & encoder;
	// distanceSensor & DistanceSensor;
	// button triggerButton;
	// button manualButton;
	// transmitInfraredMessage transmitter;
public:
	weaponManager(display & Display, weapon Weapon/*, rotaryEncode & encoder, distanceSensor & DistanceSensor, button triggerButton, button manualButton, transmitInfraredMessage transmitter*/):
		Display(Display),
		Weapon(Weapon)/*,
		encoder(encoder),
		DistanceSensor(DistanceSensor),
		triggerButton(triggerButton),
		manualButton(manualButton),
		transmitter(transmitter)
		*/
	{
		Display = display()
		/*
			hwlib::window & weaponWindow;
			hwlib::window & bulletWindow;
			hwlib::window & healthWindow;
			hwlib::window & timeWindow;
			hwlib::window & powerUpWindow;
			hwlib::terminal_from & scoreTerminal;	
		*/
	}
};

#endif /* weaponManager.hpp */
