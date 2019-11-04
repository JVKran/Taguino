#ifndef __DISPLAY_HPP
#define __DISPLAY_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "entities.hpp"
#include "scoreboard.hpp"
#include "applicationLogic.hpp"

class display : public rtos::task< 12000 > {
protected:
	hwlib::glcd_oled & oled;
	hwlib::window_part timeWindow;
	hwlib::window_part powerUpWindow;
	hwlib::window_part scoreWindow;
	hwlib::terminal_from scoreTerminal;

	// displayedData lastData;

	rtos::flag newScoreFlag;
	rtos::pool<uint8_t> newScorePool;
	uint8_t score;

	//rtos::flag newScoreBoardFlag;
	//rtos::pool<scoreboard> newScoreBoardPool;

	rtos::flag newTimeFlag;
	rtos::pool<double> newTimePool;
	double totalGameTime = 0;
	double remainingSeconds;

	rtos::flag newPowerUpFlag;
	int powerUpID;
	rtos::pool<int> newPowerUpPool;
public:
	display(hwlib::glcd_oled & oled);

	void showScoreBoard();

	void showScore(const uint8_t score);
	void drawScore();

	void showTime(const double remainingSeconds, double totalGameSeconds = 0);
	void drawTime();

	void showPowerUp(int powerUpID);
	void drawPowerUp();
	void drawMaxAmmo();
	void drawInstaKill();
	void main() override;

};

#endif /* display.hpp */