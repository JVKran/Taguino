#ifndef __DISPLAY_HPP
#define __DISPLAY_HPP

#include "hwlib.hpp"

class display{
private:
	hwlib::glcd_oled & oled;
	hwlib::window_part weaponWindow;
	hwlib::window_part bulletWindow;
	hwlib::window_part healthWindow;
	hwlib::window_part timeWindow;
	hwlib::window_part powerUpWindow;
	hwlib::terminal_from scoreTerminal;
public:
	display(hwlib::glcd_oled & oled):
		oled(oled),
		weaponWindow(oled, hwlib::xy(0,0), hwlib::xy(40,13)),
		bulletWindow(oled, hwlib::xy(0,14), hwlib::xy(41,24)),
		healthWindow(oled, hwlib::xy(0,25), hwlib::xy(40,30)),
		timeWindow(oled, hwlib::xy(78,0), hwlib::xy(128,39)),
		powerUpWindow(oled, hwlib::xy(78,40), hwlib::xy(128,64)),
		scoreTerminal(oled, hwlib::font_default_8x8())
		
	{}
	// void showBullets(int amountOfBullets);
	// void showHealth(int health);
	// void showWeapon(int weaponID);
	// void showScore(scoreboard & scoreBoard);

};

#endif /* display.hpp */