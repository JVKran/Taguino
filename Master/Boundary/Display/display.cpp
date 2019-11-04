#include "display.hpp"

display::display(hwlib::glcd_oled & oled):
	oled(oled),
	timeWindow(oled, hwlib::xy(107,21), hwlib::xy(128,41)),
	powerUpWindow(oled, hwlib::xy(78,40), hwlib::xy(128,64)),
	scoreWindow(oled, hwlib::xy(0, 0), hwlib::xy(127, 63)),
	scoreTerminal(scoreWindow, hwlib::font_default_8x8()),
	newScoreFlag(this),
	newScorePool("New Score Pool"),
	//newScoreBoardFlag(this),
	//newScoreBoardPool("New Scoreboard Pool"),
	newTimeFlag(this),
	newTimePool("New Time Pool"),
	newPowerUpFlag(this),
	newPowerUpPool("New Powerup Pool")
{
	oled.clear();
	oled.flush();
	// hwlib::cout<<"in constructor";
HWLIB_TRACE;
	scoreTerminal<<'x';//1023;
HWLIB_TRACE;
	hwlib::line(hwlib::xy(0,0), hwlib::xy(10,10)).draw(oled);
HWLIB_TRACE;
	oled.flush();
HWLIB_TRACE;
	showScore(10);
}

void display::showScore(const uint8_t score){
	newScorePool.write(score);
	newScoreFlag.set();
}

void display::drawScore(){
	scoreTerminal << '\f' << int(newScorePool.read());
}

void display::showTime(const double remainingSeconds, double totalGameSeconds){
	if(totalGameSeconds != 0){
		totalGameTime = totalGameSeconds;
	}
	newTimePool.write(remainingSeconds);
	newTimeFlag.set();
}

void display::showPowerUp(int powerUpID){
	newPowerUpPool.write(powerUpID);
	newPowerUpFlag.set();
}

void display::drawPowerUp(){
	powerUpID = newPowerUpPool.read();
	if(powerUpID == 0){
		drawMaxAmmo();
	} else if(powerUpID == 1){
		drawInstaKill();
	} else {
		powerUpWindow.flush();
	}
}

void display::drawMaxAmmo(){
	//Left Bullet
	hwlib::line(hwlib::xy(4, 5), hwlib::xy(4, 13)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(6, 5), hwlib::xy(6, 13)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(4, 13), hwlib::xy(7, 13)).draw(powerUpWindow);

	hwlib::line(hwlib::xy(5, 2), hwlib::xy(6, 5)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(5, 2), hwlib::xy(4, 5)).draw(powerUpWindow);

	//Right Bullet
	hwlib::line(hwlib::xy(16, 5), hwlib::xy(16, 13)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(18, 5), hwlib::xy(18, 13)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(16, 13), hwlib::xy(19, 13)).draw(powerUpWindow);

	hwlib::line(hwlib::xy(17, 2), hwlib::xy(18, 5)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(17, 2), hwlib::xy(16, 5)).draw(powerUpWindow);

	//Mid Bullet
	hwlib::line(hwlib::xy(10, 3), hwlib::xy(10, 11)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(12, 3), hwlib::xy(12, 11)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(10, 11), hwlib::xy(13, 11)).draw(powerUpWindow);

	hwlib::line(hwlib::xy(11, 0), hwlib::xy(10, 3)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(11, 0), hwlib::xy(12, 3)).draw(powerUpWindow);
	powerUpWindow.flush();
}

void display::drawInstaKill(){
	hwlib::line(hwlib::xy(3,0), hwlib::xy(8,0)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(2,1), hwlib::xy(9,1)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(1,2), hwlib::xy(10,2)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(1,3), hwlib::xy(10,3)).draw(powerUpWindow);
	//Eyes
	hwlib::line(hwlib::xy(3,4), hwlib::xy(5,4)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(8,4), hwlib::xy(10,4)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(3,5), hwlib::xy(5,5)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(8,5), hwlib::xy(10,5)).draw(powerUpWindow);

	hwlib::line(hwlib::xy(1,6), hwlib::xy(8,6)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(2,7), hwlib::xy(2,9)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(4,7), hwlib::xy(4,9)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(6,7), hwlib::xy(6,9)).draw(powerUpWindow);
	hwlib::line(hwlib::xy(2,7), hwlib::xy(6,7)).draw(powerUpWindow);
	powerUpWindow.flush();
}

void display::main(){
	for(;;){
		auto event = wait(/*newScoreBoardFlag+*/newTimeFlag+newPowerUpFlag+newScoreFlag);
		if (event == newTimeFlag){
			// drawTime();
		} else if (event == newPowerUpFlag){
			drawPowerUp();
		} else if (event == newScoreFlag){
			drawScore();
		}
		/*else if (event == newScoreBoardFlag){

		} */
	}
}
