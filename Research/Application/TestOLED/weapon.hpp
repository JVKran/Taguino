#ifndef __WEAPON_HPP
#define __WEAPON_HPP

#include "hwlib.hpp"

class weapon{
private:
	int damageFactor;
	hwlib::xy & position;
public:
	weapon(damageFactor):
		damageFactor(damageFactor)
	{}

	void drawWeapon(hwlib::xy & position)=0;
};

#endif /*weapon.hpp*/