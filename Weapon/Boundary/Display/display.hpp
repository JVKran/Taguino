#ifndef __DISPLAY_HPP
#define __DISPLAY_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "entities.hpp"
#include "scoreboard.hpp"
#include "applicationLogic.hpp"

class display : public rtos::task<> {
protected:
	hwlib::glcd_oled & oled;
	hwlib::window_part weaponWindow;
	hwlib::window_part weaponSettingWindow;
	hwlib::window_part fireModeWindow;
	hwlib::window_part bulletWindow;
	hwlib::window_part magazineWindow;
	hwlib::window_part healthWindow;
	hwlib::window_part timeWindow;
	hwlib::window_part powerUpWindow;
	hwlib::window_part scoreWindow;
	hwlib::terminal_from scoreTerminal;

	displayedData lastData;
	bool maxBulletsDrawn = false;
	bool maxMagazinesDrawn = false;	
	int currentlySelectedWindow = 0;

	const lookup <int, 360> xCoordinates;
	const lookup <int, 360> yCoordinates;
	void drawUnknown();
	void drawShotgun();
	void drawPistol();
	void drawSniper();
	void drawM16();
	void drawAK();
	void drawMaxAmmo();
	void drawInstaKill();

	rtos::flag newBulletFlag;
	rtos::pool<int> newBulletPool;
	int amountOfBullets;

	rtos::flag newWeaponFlag;
	rtos::pool<int> newWeaponPool;
	int weaponId;

	rtos::flag newScoreFlag;
	rtos::pool<uint8_t> newScorePool;
	uint8_t score;

	rtos::flag newMagazineFlag;
	rtos::pool<int> newMagazinePool;
	int amountOfMagazines;

	rtos::flag newHealthFlag;
	int health;
	rtos::pool<int> newHealthPool;

	//rtos::flag newScoreBoardFlag;
	//rtos::pool<scoreboard> newScoreBoardPool;

	rtos::flag newTimeFlag;
	rtos::pool<double> newTimePool;
	double totalGameTime = 0;
	double remainingSeconds;

	rtos::flag newPowerUpFlag;
	int powerUpID;
	rtos::pool<int> newPowerUpPool;

	rtos::flag newFireModeFlag;
	rtos::pool<int> newFireModePool;
	int fireMode;
public:
	display(hwlib::glcd_oled & oled, const lookup <int, 360> xCoordinates, const lookup <int, 360> yCoordinates);

	void showBullets(int amountOfBullets);
	void drawBullets(const bool draw);

	void showHealthBar();
	void showHealth(const int health);
	void updateHealth();

	void showMagazines(int amountOfMagazines);
	void drawMagazines();

	void showWeapon(int weaponID);
	void drawWeapon();

	void showScoreBoard();

	void showScore(const uint8_t score);
	void drawScore();

	void showTime(const double remainingSeconds, double totalGameSeconds = 0);
	void drawTime();

	void showPowerUp(int powerUpID);
	void drawPowerUp();

	void selectedSetting(const int setting);
	void selectedWindow(const int window);

	void showFireMode(const int mode);
	void drawFireMode();

	void main() override;

};

#endif /* display.hpp */