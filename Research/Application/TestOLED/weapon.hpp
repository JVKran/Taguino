#include "hwlib.hpp"
#include <array>

class weapon{
private:
	int weaponID;											//Weapon ID will be used as index for the arrays, to get specific data on weapon.
	// std::array<int, 3> amountOfMags;						//Amount of magazines.		
	// std::array<int, 3> magSize;								//Amount of bullets in the magazine.
	// int bulletAmount;										//Amount of bullets in the round.
	// std::array<int, 3> damageFactor;						//Amount of damage per shot.
public:
	weapon()
	{
		// weaponID=-1;										//ID on -1 so the weapontypes can start on 0.
		// std::array<int, 3> amountOfMags {8, 5, 4};			//Shotgun, pistol, assault rifle.
		// std::array<int, 3> magSize = {4, 12, 30};			//Shotgun, pistol, assault rifle.
		// bulletAmount=-1;									//BulletAmount will differ on magSizes and bullets shot.
		// std::array<int, 3> damageFactor = {80, 20, 30};		//Shotgun, pistol, assault rifle.
	}
};