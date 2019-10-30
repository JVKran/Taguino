#ifndef __DISPLAY_HPP
#define __DISPLAY_HPP

#include "hwlib.hpp"
#include "entities.hpp"
#include "scoreboard.hpp"

class display {
protected:
	hwlib::glcd_oled & oled;
	hwlib::window_part weaponWindow;
	hwlib::window_part bulletWindow;
	hwlib::window_part magazineWindow;
	hwlib::terminal_from magazineTerminal;
	hwlib::window_part healthWindow;
	hwlib::window_part timeWindow;
	hwlib::window_part powerUpWindow;
	hwlib::terminal_from scoreTerminal;

	displayedData lastData;
	bool maxBulletsDrawn = false;		

	void drawUnknown();
	void drawShotgun();
	void drawPistol();
	
public:
	display(hwlib::glcd_oled & oled):
		oled(oled),
		weaponWindow(oled, hwlib::xy(0,0), hwlib::xy(40,13)),
		bulletWindow(oled, hwlib::xy(0,16), hwlib::xy(41,26)),
		magazineWindow(oled, hwlib::xy(0,27), hwlib::xy(41,39)),
		magazineTerminal(magazineWindow, hwlib::font_default_8x8()),
		healthWindow(oled, hwlib::xy(0,40), hwlib::xy(40,46)),
		timeWindow(oled, hwlib::xy(78,0), hwlib::xy(128,39)),
		powerUpWindow(oled, hwlib::xy(78,40), hwlib::xy(128,64)),
		scoreTerminal(oled, hwlib::font_default_8x8())
	{
		oled.clear();
	}
	void terminal();
	void showBullets(int amountOfBullets);
	void showHealthBar();
	void updateHealth(const unsigned int prevHealth, const unsigned int health);
	void showMagazines(int amountOfMagazines);
	void showWeapon(int weaponID);
	void showTime(const int remainingSeconds, const int totalSeconds);
	void selectedSetting(const int setting);

};

#endif /* display.hpp */