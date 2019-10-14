#ifndef __SHOTGUN_HPP
#define __SHOTGUN_HPP

#include "hwlib.hpp"
#include "weapon.hpp"
#include "shapes.hpp"

class shotgun : public weapon{
private:
	size_t bullets;
public:
	shotgun(hwlib::window & weaponWindow):
		weapon(damageFactor, weaponWindow)
	{
		damageFactor=40;
		bullets=8;
	}

	void drawWeapon();
	void drawBullets();
};

#endif /*shotgun.hpp*/