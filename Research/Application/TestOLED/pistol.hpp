#ifndef __PISTOL_HPP
#define __PISTOL_HPP

#include "hwlib.hpp"
#include "weapon.hpp"

class pistol : public weapon{
public:
	pistol(hwlib::window & weaponWindow):
		weapon(damageFactor, weaponWindow)
	{
		damageFactor=15;
	}

	void drawWeapon();
};

#endif /*pistol.hpp*/