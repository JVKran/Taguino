#include "shotgun.hpp"

void shotgun::drawWeapon(){
	hwlib::line(hwlib::xy(0,10),hwlib::xy(12,5)).draw(weaponWindow); 	//recoilPadTop
	hwlib::line(hwlib::xy(0,11),hwlib::xy(12,6)).draw(weaponWindow); 	//recoilPadMid
	hwlib::line(hwlib::xy(0,12),hwlib::xy(12,6)).draw(weaponWindow); 	//recoilPadBottom

	hwlib::line(hwlib::xy(13,4), hwlib::xy(39,4)).draw(weaponWindow); 	//barrelTop
	hwlib::line(hwlib::xy(12,5), hwlib::xy(40,5)).draw(weaponWindow); 	//barrelMid
	hwlib::line(hwlib::xy(12,6), hwlib::xy(40,6)).draw(weaponWindow); 	//barrelBottom
	hwlib::line(hwlib::xy(22,7), hwlib::xy(35,7)).draw(weaponWindow); 	//foreEnd
	// rectangle(weaponWindow, hwlib::xy(12,5), hwlib::xy(40,7)).draw();

	weaponWindow.flush();
}