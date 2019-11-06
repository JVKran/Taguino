#include "display.hpp"

display::display(hwlib::glcd_oled & oled, const lookup <int, 360> xCoordinates, const lookup <int, 360> yCoordinates, hwlib::window_part & scoreWindow, hwlib::terminal_from & scoreTerminal, hwlib::terminal_from & scoreBoardTerminal):
	oled(oled),
	weaponWindow(oled, hwlib::xy(0,0), hwlib::xy(40,13)),
	weaponSettingWindow(oled, hwlib::xy(40, 0), hwlib::xy(50, 13)),
	fireModeWindow(oled, hwlib::xy(0, 42), hwlib::xy(41, 57)),
	bulletWindow(oled, hwlib::xy(0,16), hwlib::xy(41,26)),
	magazineWindow(oled, hwlib::xy(0,27), hwlib::xy(41,39)),
	healthWindow(oled, hwlib::xy(88,0), hwlib::xy(128,6)),
	timeWindow(oled, hwlib::xy(107,21), hwlib::xy(128,41)),
	powerUpWindow(oled, hwlib::xy(78,40), hwlib::xy(128,64)),
	scoreWindow(scoreWindow),
	scoreTerminal(scoreTerminal),
	scoreBoardTerminal(scoreBoardTerminal),
	xCoordinates(xCoordinates),
	yCoordinates(yCoordinates),
	newBulletFlag(this),
	newBulletPool("New Bullet Pool"),
	newWeaponFlag(this),
	newWeaponPool("New Weapon Pool"),
	newScoreFlag(this),
	newScorePool("New Score Pool"),
	newMagazineFlag(this),
	newMagazinePool("New Magazine Pool"),
	newHealthFlag(this),
	newHealthPool("New Health Pool"),
	//newScoreBoardFlag(this),
	//newScoreBoardPool("New Scoreboard Pool"),
	newTimeFlag(this),
	newTimePool("New Time Pool"),
	newPowerUpFlag(this),
	newPowerUpPool("New Powerup Pool"),
	newFireModeFlag(this),
	newFireModePool("New Fire Mode Pool"),
	newWindowFlag(this),
	newWindowPool("New Window Pool"),
	newSettingFlag(this),
	newSettingPool("New Setting Pool")
{
	oled.clear();
	showScore(0);
}

void display::showBullets(int amountOfBullets){
	newBulletPool.write(amountOfBullets);
	newBulletFlag.set();
}

void display::drawBullets(const bool draw){
	amountOfBullets = newBulletPool.read();
	if((amountOfBullets != lastData.lastBullets && (amountOfBullets < 10 || !maxBulletsDrawn)) || draw == true){
		for(int i=0; i<10 && i< amountOfBullets; i++){									
			hwlib::line(hwlib::xy(i*4,0), hwlib::xy(i*4,7)).draw(bulletWindow);			
		}
		if(amountOfBullets > 10){																	
			hwlib::line(hwlib::xy(39,2), hwlib::xy(39,5)).draw(bulletWindow);			
			hwlib::line(hwlib::xy(38,3), hwlib::xy(41,3)).draw(bulletWindow);			
			maxBulletsDrawn = true;			//Doesn't have to be drawn again as long as bullets isnt equal or less than 10
		}
		else if(amountOfBullets < lastData.lastBullets && amountOfBullets < 10){
			for(int i = amountOfBullets; i< lastData.lastBullets; i++){
				hwlib::line(hwlib::xy(i*4,0), hwlib::xy(i*4,7), hwlib::black).draw(bulletWindow);
			}
			if(lastData.lastBullets > 10){
				hwlib::line(hwlib::xy(39,2), hwlib::xy(39,5), hwlib::black).draw(bulletWindow);
				hwlib::line(hwlib::xy(38,3), hwlib::xy(41,3), hwlib::black).draw(bulletWindow);
			}
			maxBulletsDrawn = false;
		}
		else{
			maxBulletsDrawn = false;
		}
		lastData.lastBullets = amountOfBullets;
		bulletWindow.flush();
	}
}

void display::showHealthBar(){
	hwlib::line(hwlib::xy(0,2), hwlib::xy(4,6)).draw(healthWindow);
	hwlib::line(hwlib::xy(4,6), hwlib::xy(8,2)).draw(healthWindow);
	hwlib::line(hwlib::xy(8,2), hwlib::xy(6,0)).draw(healthWindow);
	hwlib::line(hwlib::xy(6,0), hwlib::xy(4,2)).draw(healthWindow);
	hwlib::line(hwlib::xy(4,2), hwlib::xy(2,0)).draw(healthWindow);
	hwlib::line(hwlib::xy(2,0), hwlib::xy(0,2)).draw(healthWindow);

	hwlib::line(hwlib::xy(10,1), hwlib::xy(39,1)).draw(healthWindow);										//HealthBar
	hwlib::line(hwlib::xy(10,2), hwlib::xy(39,2)).draw(healthWindow);										//HealthBar
	hwlib::line(hwlib::xy(10,3), hwlib::xy(39,3)).draw(healthWindow);										//HealthBar
	hwlib::line(hwlib::xy(10,4), hwlib::xy(39,4)).draw(healthWindow);										//HealthBar
	hwlib::line(hwlib::xy(10,5), hwlib::xy(39,5)).draw(healthWindow);										//HealthBar
	healthWindow.flush();
}

void display::updateHealth(){
	health = newHealthPool.read();
	if(health < 0 || health > 100){
		health = lastData.lastHealth;
	}
	int amountOfBlack = 27-((100 - health) * 0.27);
	int amountOfWhite = (100 - health) * 0.27;
	if(lastData.lastHealth < health){
		hwlib::line(hwlib::xy(12,2), hwlib::xy(amountOfWhite,2)).draw(healthWindow);						//White line
		hwlib::line(hwlib::xy(12,3), hwlib::xy(amountOfWhite,3)).draw(healthWindow);						//White line
		hwlib::line(hwlib::xy(12,4), hwlib::xy(amountOfWhite,4)).draw(healthWindow);						//White line
	}
	else{
		hwlib::line(hwlib::xy(11+amountOfBlack,2), hwlib::xy(38,2), hwlib::black).draw(healthWindow);		//Black line
		hwlib::line(hwlib::xy(11+amountOfBlack,3), hwlib::xy(38,3), hwlib::black).draw(healthWindow);		//Black line
		hwlib::line(hwlib::xy(11+amountOfBlack,4), hwlib::xy(38,4), hwlib::black).draw(healthWindow);		//Black line
	}
	healthWindow.flush();
	lastData.lastHealth = health;
}

void display::showHealth(const int health){
	newHealthPool.write(health);
	newHealthFlag.set();
}

void display::showMagazines(int amountOfMagazines){
	newMagazinePool.write(amountOfMagazines);
	newMagazineFlag.set();
}

void display::drawMagazines(){
	amountOfMagazines = newMagazinePool.read();
	if((amountOfMagazines < 3 || !maxMagazinesDrawn) && amountOfMagazines >= 0){
		for(int i = 0; i < 3 && i < amountOfMagazines; i++){
			hwlib::line(hwlib::xy(i*13,0), hwlib::xy(i*13+10,0)).draw(magazineWindow);						//topMagazine
			hwlib::line(hwlib::xy(i*13,0), hwlib::xy(i*13,7)).draw(magazineWindow);							//leftMagazine
			hwlib::line(hwlib::xy(i*13,7), hwlib::xy(i*13+6,7)).draw(magazineWindow);						//botMagazine
			hwlib::line(hwlib::xy(i*13+6,7), hwlib::xy(i*13+10,0)).draw(magazineWindow);					//rightMagazine
		}
		if(amountOfMagazines > 3){																	
			hwlib::line(hwlib::xy(39,2), hwlib::xy(39,5)).draw(magazineWindow);			
			hwlib::line(hwlib::xy(38,3), hwlib::xy(41,3)).draw(magazineWindow);			
			maxBulletsDrawn = true;				//Doesn't have to be drawn again as long as bullets isnt equal or less than 3
		}	
		else if(amountOfMagazines < lastData.lastMagazines && amountOfMagazines < 3){
			for(int i=amountOfMagazines; i<lastData.lastMagazines; i++){
				hwlib::line(hwlib::xy(i*13,0),hwlib::xy(i*13+10,0),hwlib::black).draw(magazineWindow);		//topMagazine
				hwlib::line(hwlib::xy(i*13,0),hwlib::xy(i*13,7),hwlib::black).draw(magazineWindow);			//leftMagazine
				hwlib::line(hwlib::xy(i*13,7),hwlib::xy(i*13+6,7),hwlib::black).draw(magazineWindow);		//botMagazine
				hwlib::line(hwlib::xy(i*13+6,7),hwlib::xy(i*13+10,0),hwlib::black).draw(magazineWindow);	//rightMagazine
			}
			if(lastData.lastMagazines > 3){
				hwlib::line(hwlib::xy(39,2), hwlib::xy(39,5), hwlib::black).draw(magazineWindow);
				hwlib::line(hwlib::xy(38,3), hwlib::xy(41,3), hwlib::black).draw(magazineWindow);
			}
			maxMagazinesDrawn = false;
		}
		else{
			maxMagazinesDrawn = false;
		}
		lastData.lastMagazines = amountOfMagazines;
		magazineWindow.flush();
	}
}

void display::showWeapon(int weaponID){
	newWeaponPool.write(weaponID);
	lastData.lastWeaponId = weaponID;
	newWeaponFlag.set();
}

void display::drawWeapon(){
	showWeapon(lastData.lastWeaponId);
}

void display::drawUnknown(){ 
	weaponWindow.clear();
	hwlib::line(hwlib::xy(0,0), hwlib::xy(41,13)).draw(weaponWindow);				//Draw the top line for a cross
	hwlib::line(hwlib::xy(0,13), hwlib::xy(41,0)).draw(weaponWindow);				//Draw the bottom line for a cross
	weaponWindow.flush();
}

void display::drawShotgun(){
	weaponWindow.clear();
	hwlib::line(hwlib::xy(0,10), hwlib::xy(12,5)).draw(weaponWindow); 				//recoilPadTop
	hwlib::line(hwlib::xy(0,11), hwlib::xy(12,6)).draw(weaponWindow); 				//recoilPadMid
	hwlib::line(hwlib::xy(0,12), hwlib::xy(12,6)).draw(weaponWindow); 				//recoilPadBottom

	hwlib::line(hwlib::xy(12,4), hwlib::xy(39,4)).draw(weaponWindow);				//topBarrel
	hwlib::line(hwlib::xy(12,6), hwlib::xy(39,6)).draw(weaponWindow);				//botBarrel
	hwlib::line(hwlib::xy(12,5), hwlib::xy(12,5)).draw(weaponWindow);				//leftBarrel
	hwlib::line(hwlib::xy(39,3), hwlib::xy(39,7)).draw(weaponWindow);				//rightBarrel

	hwlib::line(hwlib::xy(23,7), hwlib::xy(36,7)).draw(weaponWindow);				//foreEnd

	weaponWindow.flush();
}

void display::drawPistol(){
	weaponWindow.clear();

	hwlib::line(hwlib::xy(2,2), hwlib::xy(19,2)).draw(weaponWindow);				//topBarrel
	hwlib::line(hwlib::xy(2,6), hwlib::xy(19,6)).draw(weaponWindow);				//botBarrel
	hwlib::line(hwlib::xy(2,3), hwlib::xy(2,7)).draw(weaponWindow);					//leftBarrel
	hwlib::line(hwlib::xy(19,1), hwlib::xy(19,7)).draw(weaponWindow);				//rightBarrel
	hwlib::line(hwlib::xy(13,5), hwlib::xy(19,5)).draw(weaponWindow);				//lineInBarrel

	hwlib::line(hwlib::xy(3,5), hwlib::xy(7,5)).draw(weaponWindow);					//topGrip
	hwlib::line(hwlib::xy(3,5), hwlib::xy(3,13)).draw(weaponWindow);				//leftGrip
	hwlib::line(hwlib::xy(3,12), hwlib::xy(8,12)).draw(weaponWindow);				//botGrip
	hwlib::line(hwlib::xy(8,12), hwlib::xy(7,5)).draw(weaponWindow);				//rightGrip

	hwlib::line(hwlib::xy(7, 9), hwlib::xy(10, 6)).draw(weaponWindow); 				//Trigger

	weaponWindow.flush();
}

void display::drawSniper(){
	weaponWindow.clear();

	hwlib::line(hwlib::xy(0,5), hwlib::xy(8,5)).draw(weaponWindow);
	hwlib::line(hwlib::xy(0,5), hwlib::xy(0,9)).draw(weaponWindow);
	hwlib::line(hwlib::xy(0,9), hwlib::xy(9,7)).draw(weaponWindow);
	hwlib::line(hwlib::xy(9,7), hwlib::xy(12,10)).draw(weaponWindow);

	hwlib::line(hwlib::xy(8,6), hwlib::xy(15,6)).draw(weaponWindow);
	hwlib::line(hwlib::xy(15,5), hwlib::xy(40,5)).draw(weaponWindow);
	hwlib::line(hwlib::xy(30,6),hwlib::xy(40,6)).draw(weaponWindow);

	hwlib::line(hwlib::xy(30,6), hwlib::xy(30,8)).draw(weaponWindow);
	hwlib::line(hwlib::xy(17,8), hwlib::xy(30,8)).draw(weaponWindow);
	hwlib::line(hwlib::xy(16,10),hwlib::xy(17,8)).draw(weaponWindow);
	hwlib::line(hwlib::xy(12,10),hwlib::xy(16,10)).draw(weaponWindow);

	hwlib::line(hwlib::xy(10,2), hwlib::xy(27,2)).draw(weaponWindow);
	hwlib::line(hwlib::xy(10,3), hwlib::xy(27,3)).draw(weaponWindow);
	hwlib::line(hwlib::xy(27,0), hwlib::xy(27,2)).draw(weaponWindow);

	hwlib::line(hwlib::xy(15,4), hwlib::xy(15,5)).draw(weaponWindow);
	hwlib::line(hwlib::xy(22,4), hwlib::xy(22,5)).draw(weaponWindow);

	weaponWindow.flush();

}

void display::drawM16(){
	weaponWindow.clear();

	hwlib::line(hwlib::xy(9,5), hwlib::xy(30,5)).draw(weaponWindow);
	hwlib::line(hwlib::xy(2,6), hwlib::xy(9,6)).draw(weaponWindow);
	hwlib::line(hwlib::xy(0,11), hwlib::xy(2,5)).draw(weaponWindow);
	hwlib::line(hwlib::xy(0,11), hwlib::xy(3,11)).draw(weaponWindow);
	hwlib::line(hwlib::xy(3,11), hwlib::xy(8,9)).draw(weaponWindow);
	hwlib::line(hwlib::xy(8,9), hwlib::xy(6,14)).draw(weaponWindow);
	hwlib::line(hwlib::xy(6,14), hwlib::xy(9,14)).draw(weaponWindow);
	hwlib::line(hwlib::xy(9,14), hwlib::xy(11,9)).draw(weaponWindow); 
	hwlib::line(hwlib::xy(11,9), hwlib::xy(13,9)).draw(weaponWindow);
	hwlib::line(hwlib::xy(13,9), hwlib::xy(13,12)).draw(weaponWindow);
	hwlib::line(hwlib::xy(13,12), hwlib::xy(17,18)).draw(weaponWindow);
	hwlib::line(hwlib::xy(17,18), hwlib::xy(21,18)).draw(weaponWindow);
	hwlib::line(hwlib::xy(21,18), hwlib::xy(17,9)).draw(weaponWindow);
	hwlib::line(hwlib::xy(18,11), hwlib::xy(22,7)).draw(weaponWindow);
	hwlib::line(hwlib::xy(20,7), hwlib::xy(21,8)).draw(weaponWindow);
	hwlib::line(hwlib::xy(21,8), hwlib::xy(30,8)).draw(weaponWindow);
	hwlib::line(hwlib::xy(30,8), hwlib::xy(30,3)).draw(weaponWindow);

	weaponWindow.flush();

}

void display::drawAK(){
	weaponWindow.clear();

	hwlib::line(hwlib::xy(0,3), hwlib::xy(3,3)).draw(weaponWindow);
	hwlib::line(hwlib::xy(0,3), hwlib::xy(0,7)).draw(weaponWindow);
	hwlib::line(hwlib::xy(0,7), hwlib::xy(11,4)).draw(weaponWindow);

	hwlib::line(hwlib::xy(3,2), hwlib::xy(11,2)).draw(weaponWindow);

	hwlib::line(hwlib::xy(11,1), hwlib::xy(33,1)).draw(weaponWindow);
	hwlib::line(hwlib::xy(22,0), hwlib::xy(25,0)).draw(weaponWindow);

	hwlib::line(hwlib::xy(11,4), hwlib::xy(9,9)).draw(weaponWindow);
	hwlib::line(hwlib::xy(9,9), hwlib::xy(13,9)).draw(weaponWindow);
	hwlib::line(hwlib::xy(13,9), hwlib::xy(18,4)).draw(weaponWindow);
	hwlib::line(hwlib::xy(18,4), hwlib::xy(22,4)).draw(weaponWindow);
	hwlib::line(hwlib::xy(22,4), hwlib::xy(26,10)).draw(weaponWindow);
	hwlib::line(hwlib::xy(26,10), hwlib::xy(31,10)).draw(weaponWindow);
	hwlib::line(hwlib::xy(32,10), hwlib::xy(28,4)).draw(weaponWindow);

	hwlib::line(hwlib::xy(28,4), hwlib::xy(33,4)).draw(weaponWindow);
	hwlib::line(hwlib::xy(33,4), hwlib::xy(33,1)).draw(weaponWindow);
	hwlib::line(hwlib::xy(33,2), hwlib::xy(40,2)).draw(weaponWindow);
	hwlib::line(hwlib::xy(33,4), hwlib::xy(40,4)).draw(weaponWindow);

	hwlib::line(hwlib::xy(40,4), hwlib::xy(40,0)).draw(weaponWindow);

	weaponWindow.flush();

}

void drawUpdatedWeaponData(){
	
}

void display::showScore(const int score){
	newScorePool.write(score);
	newScoreFlag.set();
}

void display::drawScore(){
	score = newScorePool.read();
	//hwlib::cout << score << hwlib::endl;
	if(score >= 0){
		scoreTerminal << '\f' << hwlib::setw(5) << hwlib::right << score << hwlib::flush;
	}
}

void display::showTime(const double remainingSeconds, double totalGameSeconds){
	if(totalGameSeconds != 0){
		totalGameTime = totalGameSeconds;
	}
	newTimePool.write(remainingSeconds);
	newTimeFlag.set();
}

void display::drawTime(){
	if(currentlySelectedWindow == 0){
		remainingSeconds = newTimePool.read();
		hwlib::circle(hwlib::xy(10,10), 10).draw(timeWindow);
		double LocationToBeFilled = (1-(remainingSeconds/ totalGameTime)) * 360;
		for(int i = 0;i <LocationToBeFilled; i++){
			if(i < 181){
				hwlib::line(hwlib::xy(10,10), hwlib::xy(xCoordinates.get(i+179) + 10, yCoordinates.get(i+179) + 10)).draw(timeWindow);
			}else{
				hwlib::line(hwlib::xy(10,10), hwlib::xy(xCoordinates.get(i-179) + 10, yCoordinates.get(i-179) + 10)).draw(timeWindow);
			}
		}
		timeWindow.flush();
	}
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
void display::selectedSetting(const int setting){
	hwlib::cout << "Encoder Pressed while on position " << setting << "." << hwlib::endl;
	newSettingPool.write(setting);
	newSettingFlag.set();
}

void display::drawSetting(){
	setting = newSettingPool.read();
	switch(setting){
		case 0:
			//Selected to change weapon
			hwlib::cout << "Setting weapon." << hwlib::endl;
			hwlib::circle(hwlib::xy(5, 5), 2).draw(weaponSettingWindow);
			weaponSettingWindow.flush();
			break;
		case 1:
			//Selected to activate powerups
			hwlib::cout << "Setting setting." << hwlib::endl;
			hwlib::circle(hwlib::xy(90,45), 2).draw(oled);
			oled.flush();
			break;
		case -1:
			//Selected to quit setting
			hwlib::cout << "Finished setting." << hwlib::endl;
			hwlib::circle(hwlib::xy(5,5), 2, hwlib::black).draw(weaponSettingWindow);
			hwlib::circle(hwlib::xy(90,45), 2, hwlib::black).draw(oled);
			oled.flush();
			break;
	}
}

void display::selectedWindow(const int window){
	newWindowPool.write(window);
	newWindowFlag.set();
}

void display::drawSelectedWindow(){
	window = newWindowPool.read();
	switch(window){
		case 0:
			hwlib::cout << "Stats being printed!" << hwlib::endl;
			currentlySelectedWindow = 0;
			oled.clear();
			showTime(remainingSeconds, totalGameTime);
			drawWeapon();
			drawBullets(true);
			drawMagazines();
			showHealthBar();
			//showScore();
			drawFireMode();
			updateHealth();
			break;
		case 1:
			hwlib::cout << "Scoreboard being printed!" << hwlib::endl;
			currentlySelectedWindow = 1;
			oled.clear();
			oled.flush();
			Scoreboard.printScoreboard();
		default:
			break;
	}
}

void display::showFireMode(const int mode){
	newFireModePool.write(mode);
	newFireModeFlag.set();
}

void display::drawFireMode(){
	fireMode = newFireModePool.read();
	fireModeWindow.clear();
	switch(fireMode){
		case 0:		//Manual
			hwlib::line(hwlib::xy(7,0), hwlib::xy(7,12)).draw(fireModeWindow);
			hwlib::line(hwlib::xy(0,10), hwlib::xy(7,0)).draw(fireModeWindow);
			hwlib::line(hwlib::xy(7,0), hwlib::xy(14,10)).draw(fireModeWindow);
			hwlib::line(hwlib::xy(14,10), hwlib::xy(0,10)).draw(fireModeWindow);
			break;
		case 1:		//AutoFire
			hwlib::line(hwlib::xy(0,10), hwlib::xy(7,0)).draw(fireModeWindow);
			hwlib::line(hwlib::xy(7,0), hwlib::xy(14,10)).draw(fireModeWindow);
			hwlib::line(hwlib::xy(14,10), hwlib::xy(0,10)).draw(fireModeWindow);
			hwlib::line(hwlib::xy(3,6),hwlib::xy(12,6)).draw(fireModeWindow);
			break;
		case 2:		//Burst
			hwlib::line(hwlib::xy(0,10), hwlib::xy(7,0)).draw(fireModeWindow);
			hwlib::line(hwlib::xy(7,0), hwlib::xy(14,10)).draw(fireModeWindow);
			hwlib::line(hwlib::xy(14,10), hwlib::xy(0,10)).draw(fireModeWindow);
			hwlib::line(hwlib::xy(2,7),hwlib::xy(13,7)).draw(fireModeWindow);
			hwlib::line(hwlib::xy(3,4),hwlib::xy(12,4)).draw(fireModeWindow);
			hwlib::line(hwlib::xy(7,0), hwlib::xy(7,12)).draw(fireModeWindow);
			break;
		default:
			break;
	}
	fireModeWindow.flush();
}

void display::main(){
	for(;;){
		auto event = wait(newBulletFlag+newMagazineFlag+newHealthFlag+/*newScoreBoardFlag+*/newTimeFlag+newPowerUpFlag+newScoreFlag+newWeaponFlag+newFireModeFlag+newWindowFlag+newSettingFlag);
		if(event == newBulletFlag){
			drawBullets(false);
		} else if (event == newMagazineFlag){
			drawMagazines();
		} else if (event == newHealthFlag){
			updateHealth();
		} else if (event == newTimeFlag){
			drawTime();
		} else if (event == newPowerUpFlag){
			drawPowerUp();
		} else if (event == newScoreFlag){
			drawScore();
		} else if (event == newFireModeFlag){
			drawFireMode();
		} else if (event == newWindowFlag){
			drawSelectedWindow();
		} else if (event == newSettingFlag){
			drawSetting();
		} else if (event == newWeaponFlag){
			weaponId = newWeaponPool.read();
			switch(weaponId){
				case 0: 
					drawShotgun();
					break;
				case 1: 
					drawPistol();
					break;
				case 2:
					drawSniper();
					break;
				case 3:
					drawAK();
					break;
				case 4:
					drawM16();
					break;
				default:
					drawUnknown();
			}
		}
		/*else if (event == newScoreBoardFlag){

		} */
	}
}
