#ifndef __SHOTGUN_HPP
#define __SHOTGUN_HPP

#include "hwlib.hpp"
#include "weapon.hpp"

class shotgun : public weapon{
public:
	shotgun(hwlib::window & weaponWindow):
		weapon(damageFactor, weaponWindow)
	{
		damageFactor=20;
	}

	void drawWeapon();
};

#endif /*shotgun.hpp*/