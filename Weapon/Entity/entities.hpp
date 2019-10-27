#ifndef __ENTITIES_HPP
#define __ENTITIES_HPP

#include "hwlib.hpp"

class player {
private:
	hwlib::string name;
	fireArm weapon;


};

class fireArm {
private:
	unsigned int amountOfBullets;

	hwlib::pin_in & triggerPin;				//Pull the trigger to shoot
	hwlib::pin_in & autoPin;				//Select automatic operation mode
	hwlib::pin_in & manualPin;				//Select manual operation mode

	weaponBullet bullet;

}

class weaponBullet {
private:
	HCSR04 & distanceSensor;
	transmitter & irTransmitter;
public:
	bullet(HCSR04 & distanceSensor, transmitter & irTransmitter);

	void fire();
}


#endif //__ENTITIES_HPP