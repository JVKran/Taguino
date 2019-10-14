#include "pistol.hpp"

void pistol::drawWeapon(){
	
	hwlib::line(hwlib::xy(5,4),hwlib::xy(20,4)).draw(weaponWindow);	//Top Barrel
	hwlib::line(hwlib::xy(5,8),hwlib::xy(20,8)).draw(weaponWindow);	//Bottom Barrel
	hwlib::line(hwlib::xy(20,4),hwlib::xy(20,8)).draw(weaponWindow);//Right Barrel
	hwlib::line(hwlib::xy(5,4),hwlib::xy(5,8)).draw(weaponWindow); //Left Barrel

	hwlib::line(hwlib::xy(5,8),hwlib::xy(5,16)).draw(weaponWindow); //Left Handhold
	hwlib::line(hwlib::xy(9,8),hwlib::xy(9,16)).draw(weaponWindow); //Right Handhold
	hwlib::line(hwlib::xy(5,15),hwlib::xy(9,15)).draw(weaponWindow); //Bottom Handhold

	hwlib::line(hwlib::xy(9, 11), hwlib::xy(12, 8)).draw(weaponWindow); //Trigger
	hwlib::line(hwlib::xy(21,5),hwlib::xy(21,7)).draw(weaponWindow); //Bullethole
	weaponWindow.flush();
}
