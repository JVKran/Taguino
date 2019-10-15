#include "pistol.hpp"

void pistol::drawWeapon(){
	auto barrelStart = hwlib::xy(5,4);
	auto barrelEnd = hwlib::xy(21,8);
	rectangle(weaponWindow, barrelStart, barrelEnd).print();

	auto handHoldStart = hwlib::xy(5,7);
	auto handHoldEnd = hwlib::xy(9,15);
	rectangle(weaponWindow, handHoldStart, handHoldEnd).print();

	hwlib::line(hwlib::xy(9, 11), hwlib::xy(12, 8)).draw(weaponWindow); //Trigger
	hwlib::line(hwlib::xy(21,5),hwlib::xy(21,7)).draw(weaponWindow); 	//Bullethole
	weaponWindow.flush();
}
