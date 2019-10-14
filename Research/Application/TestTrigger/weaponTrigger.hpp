#ifndef  __WEAPONTRIGGER_HPP
#define __WEAPONTRIGGER_HPP

#include "hwlib.hpp"

class weaponTrigger{
private:
	hwlib::target::pin_in & weaponTriggerPin;
public:
	weaponTrigger(hwlib::target::pin_in & weaponTriggerPin):
		weaponTriggerPin(weaponTriggerPin)
	{}

	bool detectTrigger();
};

#endif /*weaponTrigger.hpp*/