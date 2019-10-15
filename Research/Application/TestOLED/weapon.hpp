#ifndef __WEAPON_HPP
#define __WEAPON_HPP

#include "hwlib.hpp"

class weapon{
protected:
	unsigned int ID;
	unsigned int magSize;
	unsigned int amountOfMags;
	unsigned int damageFactor;
	hwlib::window & weaponWindow;
	hwlib::window & bulletsWindow;
public:
	weapon(unsigned int ID, unsigned int magSize, unsigned int amountOfMags, unsigned int damageFactor, hwlib::window & weaponWindow, hwlib::window & bulletsWindow):
		ID(ID),
		magSize(magSize),
		damageFactor(damageFactor),
		weaponWindow(weaponWindow),
		bulletsWindow(bulletsWindow)
	{
		damageFactor = 10;
	}

	virtual void drawWeapon()=0;
	virtual void drawBullets();
	void upBullets();
};

class shotgun : public weapon{
public:
	shotgun(hwlib::window & weaponWindow, hwlib::window & bulletsWindow):
		weapon(ID, magSize, amountOfMags, damageFactor, weaponWindow, bulletsWindow)
	{
		ID=1;
		damageFactor=50;
		magSize=4;
		amountOfMags=8;
	}

	void drawWeapon();
};

class pistol : public weapon{
public:
	pistol(hwlib::window & weaponWindow, hwlib::window & bulletsWindow):
		weapon(ID, magSize, amountOfMags, damageFactor, weaponWindow, bulletsWindow)
	{
		ID=2;
		damageFactor=15;
		magSize=12;
		amountOfMags=5;
	}

	void drawWeapon();
};
#endif /*weapon.hpp*/