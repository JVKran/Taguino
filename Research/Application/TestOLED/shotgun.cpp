#include "shotgun.hpp"

void shotgun::drawWeapon(){
	hwlib::line(hwlib::xy(0,10),hwlib::xy(12,5)).draw(weaponWindow); 	//recoilPadTop
	hwlib::line(hwlib::xy(0,11),hwlib::xy(12,6)).draw(weaponWindow); 	//recoilPadMid
	hwlib::line(hwlib::xy(0,12),hwlib::xy(12,6)).draw(weaponWindow); 	//recoilPadBottom

	auto barrelStart = hwlib::xy(12,4);
	auto barrelEnd = hwlib::xy(40,6);
	rectangle(weaponWindow, barrelStart, barrelEnd).print();
	
	auto foreEndStart = hwlib::xy(24,6);
	auto foreEndEnd = hwlib::xy(34,7);
	rectangle(weaponWindow, foreEndStart, foreEndEnd).print();

	weaponWindow.flush();
}