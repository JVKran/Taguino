#ifndef __WEAPON_HPP
#define __WEAPON_HPP

#include "hwlib.hpp"

class weapon{
protected:
	int damageFactor;
	hwlib::window & weaponWindow;
public:
	weapon(int damageFactor, hwlib::window & weaponWindow):
		damageFactor(damageFactor),
		weaponWindow(weaponWindow)
	{
		damageFactor = 10;
	}

	virtual void drawWeapon()=0;
};

#endif /*weapon.hpp*/