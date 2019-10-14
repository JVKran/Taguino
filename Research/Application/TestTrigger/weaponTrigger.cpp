#include "weaponTrigger.hpp"

bool weaponTrigger::detectTrigger(){
	bool pressed = weaponTriggerPin.read();
	return !pressed; 						// Invert pressed, since it uses a pull-up. 
}											// now it returns 0 for not pressed and 1 for pressed