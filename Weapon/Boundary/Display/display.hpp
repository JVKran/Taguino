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
	hwlib::window_part bulletWindow;
	hwlib::window_part magazineWindow;
	hwlib::window_part healthWindow;
	hwlib::window_part timeWindow;
	hwlib::window_part powerUpWindow;
	hwlib::terminal_from scoreTerminal;

	displayedData lastData;
	bool maxBulletsDrawn = false;
	bool maxMagazinesDrawn = false;	

	const lookup <int, 360> xCoordinates;
	const lookup <int, 360> yCoordinates;
	void drawUnknown();
	void drawShotgun();
	void drawPistol();
	void drawMaxAmmo();
	void drawInstaKill();

	rtos::flag newBulletFlag;
	rtos::pool<int> newBulletPool;
	int amountOfBullets;

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
	const double totalGameTime;
	double remainingSeconds;

	rtos::flag newPowerUpFlag;
	int powerUpID;
	rtos::pool<int> newPowerUpPool;
public:
	display(hwlib::glcd_oled & oled, const lookup <int, 360> xCoordinates, const lookup <int, 360> yCoordinates, const int gameTime);

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

	void showTime(const double remainingSeconds);
	void drawTime();

	void showPowerUp(int powerUpID);
	void drawPowerUp();

	void selectedSetting(const int setting);
	void selectedWindow(const int window);

	void main() override;

};

#endif /* display.hpp */