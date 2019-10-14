#ifndef __ASSAULTRIFLE_HPP
#define __ASSAULTRIFLE_HPP

#include "hwlib.hpp"
#include "weapon.hpp"

class assaultRifle : public weapon{
public:
	shotgun(hwlib::window & weaponWindow):
		weapon(damageFactor, weaponWindow)
	{
		damageFactor=10;
	}

	void drawWeapon();
};

#endif /*assaultRifle.hpp*/