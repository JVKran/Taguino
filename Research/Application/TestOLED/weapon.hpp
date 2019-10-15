#ifndef __WEAPON_HPP
#define __WEAPON_HPP

#include "hwlib.hpp"

class weapon{
protected:
	unsigned int ID;															//Weapon ID
	unsigned int magSize;														//Amount of bullets per magazine
	unsigned int amountOfMags;													//Amount of magazines available
	unsigned int damageFactor;													//Damagefactor per shot
	hwlib::window & weaponWindow;												//Window to print weapon
	hwlib::window & bulletsWindow;												//Window to print bullets
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

	virtual void drawWeapon()=0;												//Virtual abstract function so every weapon gets to draw it's own image
	virtual void drawBullets();													//Function that draws amount of bullets up to 10, adds a "+" sign if it's more then 10
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