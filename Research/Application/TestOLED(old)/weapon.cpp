#include "weapon.hpp"

void shotgun::drawWeapon(){															//Finished image of a shotgun
		hwlib::line(hwlib::xy(0,10),hwlib::xy(12,5)).draw(weaponWindow); 				//recoilPadTop
	hwlib::line(hwlib::xy(0,11),hwlib::xy(12,6)).draw(weaponWindow); 				//recoilPadMid
	hwlib::line(hwlib::xy(0,12),hwlib::xy(12,6)).draw(weaponWindow); 				//recoilPadBottom

	hwlib::line(hwlib::xy(12,4), hwlib::xy(39,4)).draw(weaponWindow);				//topBarrel
	hwlib::line(hwlib::xy(12,6), hwlib::xy(39,6)).draw(weaponWindow);				//botBarrel
	hwlib::line(hwlib::xy(12,5), hwlib::xy(12,5)).draw(weaponWindow);				//leftBarrel
	hwlib::line(hwlib::xy(39,3), hwlib::xy(39,7)).draw(weaponWindow);				//rightBarrel

	hwlib::line(hwlib::xy(23,7), hwlib::xy(36,7)).draw(weaponWindow);				//foreEnd

	weaponWindow.flush();
}

void pistol::drawWeapon(){															//Unfinished image of pistol
	/*auto barrelStart = hwlib::xy(5,4);
	auto barrelEnd = hwlib::xy(21,8);
	rectangle(weaponWindow, barrelStart, barrelEnd).print();

	auto handHoldStart = hwlib::xy(5,7);
	auto handHoldEnd = hwlib::xy(9,15);
	rectangle(weaponWindow, handHoldStart, handHoldEnd).print();

	hwlib::line(hwlib::xy(9, 11), hwlib::xy(12, 8)).draw(weaponWindow); //Trigger
	hwlib::line(hwlib::xy(23,5),hwlib::xy(21,7)).draw(weaponWindow); 	//Bullethole
	weaponWindow.flush();
	*/															
}

void weapon::drawBullets(){
	for(size_t i=0; i<10 && i<magSize; i++){										//Line for every bullet up to 10 bullets
		hwlib::line(hwlib::xy(i*4,0),hwlib::xy(i*4,7)).draw(bulletsWindow);			
	}
	if(magSize>10){																	//If mag has more then 10 bullets in it/ left
		hwlib::line(hwlib::xy(39,2), hwlib::xy(39,5)).draw(bulletsWindow);			//Vertical line for "+" sign
		hwlib::line(hwlib::xy(38,3), hwlib::xy(41,3)).draw(bulletsWindow);			//Horizontal line for "+" sign
	}
	bulletsWindow.flush();
}