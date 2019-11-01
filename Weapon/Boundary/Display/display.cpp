#include "display.hpp"

display::display(hwlib::glcd_oled & oled, const lookup <int, 360> xCoordinates, const lookup <int, 360> yCoordinates, const int gameTime):
	oled(oled),
	weaponWindow(oled, hwlib::xy(0,0), hwlib::xy(40,13)),
	bulletWindow(oled, hwlib::xy(0,16), hwlib::xy(41,26)),
	magazineWindow(oled, hwlib::xy(0,27), hwlib::xy(41,39)),
	healthWindow(oled, hwlib::xy(88,0), hwlib::xy(128,6)),
	timeWindow(oled, hwlib::xy(107,8), hwlib::xy(128,29)),
	powerUpWindow(oled, hwlib::xy(78,40), hwlib::xy(128,64)),
	scoreTerminal(oled, hwlib::font_default_8x8()),
	xCoordinates(xCoordinates),
	yCoordinates(yCoordinates),
	newBulletFlag(this),
	newBulletPool("New Bullet Pool"),
	newMagazineFlag(this),
	newMagazinePool("New Magazine Pool"),
	newHealthFlag(this),
	newHealthPool("New Health Pool"),
	//newScoreBoardFlag(this),
	//newScoreBoardPool("New Scoreboard Pool"),
	newTimeFlag(this),
	newTimePool("New Time Pool"),
	totalGameTime(gameTime),
	newPowerUpFlag(this),
	newPowerUpPool("New Powerup Pool")
{
	oled.clear();
}

void display::showBullets(int amountOfBullets){
	newBulletFlag.set();
	newBulletPool.write(amountOfBullets);
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
	newHealthFlag.set();
	newHealthPool.write(health);
}

void display::showMagazines(int amountOfMagazines){
	newMagazineFlag.set();
	newMagazinePool.write(amountOfMagazines);
}

void display::drawMagazines(const bool draw){
	amountOfMagazines = newMagazinePool.read();
	if((amountOfMagazines != lastData.lastMagazines && (amountOfMagazines < 3 || !maxMagazinesDrawn))|| draw == true){
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
	}
	magazineWindow.flush();
}

void display::showWeapon(int weaponID){
	switch(weaponID){
		case 0: 
			drawShotgun();
			break;
		case 1: 
			drawPistol();
			break;
		default:
			drawUnknown();
	}
	lastData.lastWeaponId = weaponID;
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

void display::showTime(const double remainingSeconds){
	newTimeFlag.set();
	newTimePool.write(remainingSeconds);
}

void display::drawTime(){
	remainingSeconds = newTimePool.read();
	hwlib::cout<<int(remainingSeconds)<<'\n';
	hwlib::circle(hwlib::xy(10,10), 10).draw(timeWindow);
	double LocationToBeFilled = (1-(remainingSeconds/ totalGameTime)) * 360;
	//hwlib::cout << "Total: " << totalGameTime << ", Remaining: " << remainingSeconds << ", LocationToBeFilled: " << int(LocationToBeFilled) << hwlib::endl;
	for(int i = 0;i <LocationToBeFilled; i++){
		if(i < 181){
			hwlib::line(hwlib::xy(10,10), hwlib::xy(xCoordinates.get(i+179) + 10, yCoordinates.get(i+179) + 10)).draw(timeWindow);
		}else{
			hwlib::line(hwlib::xy(10,10), hwlib::xy(xCoordinates.get(i-179) + 10, yCoordinates.get(i-179) + 10)).draw(timeWindow);
		}
	}
	timeWindow.flush();
}

void display::showPowerUp(int powerUpID){
	newPowerUpFlag.set();
	newPowerUpPool.write(powerUpID);
}

void display::drawPowerUp(){
	powerUpID = newPowerUpPool.read();
	if(powerUpID == 0){
		drawMaxAmmo();
	}
	else if(powerUpID == 1){
		drawInstaKill();
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
}
void display::selectedSetting(const int setting){
	hwlib::cout << "Encoder Pressed while on position " << setting << "." << hwlib::endl;

	//CIRCLES DO NOT DISAPEAR
	//WILL HAVE TO ADD THIS WHEN IT'S IMPLEMENTED
	//EASILY DONE WITH A BLACK CIRCLE
	switch(setting){
		case 0:
			//Selected to change weapon
			hwlib::cout << "Setting weapon." << hwlib::endl;
			hwlib::circle(hwlib::xy(50,5), 2).draw(oled);
			oled.flush();
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
			hwlib::circle(hwlib::xy(50,5), 2, hwlib::black).draw(oled);
			hwlib::circle(hwlib::xy(90,45), 2, hwlib::black).draw(oled);
			oled.flush();
			break;
	}
}

void display::showScoreBoard(){
	const char * playerName1 = "Jochem";	//This would usually be received from the master...
   playerData player1 = playerData(playerName1, 1, 1);
   weaponData weapon1 = weaponData(2);

   const char * playerName2 = "Stefan"; //This would usually be received from the master...
   playerData player2 = playerData(playerName2, 1, 1);
   weaponData weapon2 = weaponData(2);

   const char * playerName3 = "Joshua"; //This would usually be received from the master...
   playerData player3 = playerData(playerName3, 1, 1);
   weaponData weapon3 = weaponData(2);

   const char * playerName4 = "Faizal"; //This would usually be received from the master...
   playerData player4 = playerData(playerName4, 1, 1);
   weaponData weapon4 = weaponData(2);

   const char * playerName5 = "Menno"; //This would usually be received from the master...
   playerData player5 = playerData(playerName5, 1, 1);
   weaponData weapon5 = weaponData(2);

   std::array<playerData,5> players = {player1, player2, player3, player4, player5};
   auto window = hwlib::window_part(oled, hwlib::xy(0,0), hwlib::xy(128, 64));

	auto windowFont 			= hwlib::font_default_8x8();
	auto windowName 			= hwlib::window_part(window, hwlib::xy(114, 3), hwlib::xy(122, 12));
	auto windowNameTerminal 	= hwlib::terminal_from(windowName, windowFont);
	hwlib::circle nameCircle	= hwlib::circle(hwlib::xy(117, 6), 5);

	auto windowPartFirstPlace 	= hwlib::window_part(window, hwlib::xy(0,10), hwlib::xy(124, 20));
	auto windowPartSecondPlace 	= hwlib::window_part(window, hwlib::xy(0,21), hwlib::xy(124, 31));
	auto windowPartThirdPlace 	= hwlib::window_part(window, hwlib::xy(0,32), hwlib::xy(124, 42));
	auto windowPartFourthPlace 	= hwlib::window_part(window, hwlib::xy(0,43), hwlib::xy(124, 53));
	auto windowPartFifthPlace 	= hwlib::window_part(window, hwlib::xy(0,54), hwlib::xy(124, 64));

	auto terminalFirstPlace 	= hwlib::terminal_from(windowPartFirstPlace, windowFont);
	auto terminalSecondPlace 	= hwlib::terminal_from(windowPartSecondPlace, windowFont);
	auto terminalThirdPlace 	= hwlib::terminal_from(windowPartThirdPlace, windowFont);
	auto terminalFourthPlace 	= hwlib::terminal_from(windowPartFourthPlace, windowFont);
	auto terminalFifthPlace 	= hwlib::terminal_from(windowPartFifthPlace, windowFont);


	terminalFirstPlace 	<< hwlib::left <<hwlib::setw(11) << players[0].getName() << players[0].getScore();
	terminalSecondPlace << hwlib::left <<hwlib::setw(11) << players[1].getName() << players[1].getScore();
	terminalThirdPlace 	<< hwlib::left <<hwlib::setw(11) << players[2].getName() << players[2].getScore();
	terminalFourthPlace << hwlib::left <<hwlib::setw(11) << players[3].getName() << players[3].getScore();
	terminalFifthPlace 	<< hwlib::left <<hwlib::setw(11) << players[4].getName() << players[4].getScore();
	
	windowNameTerminal 	<< 'B';
	windowNameTerminal.flush();
	nameCircle.draw(oled);
}

void display::selectedWindow(const int window){
	switch(window){
		case 0:
			oled.clear();
			drawTime();
			drawWeapon();
			drawBullets(true);
			drawMagazines(true);
			showHealthBar();
			updateHealth();
			drawInstaKill();
			break;
		case 1:
			oled.clear();
			showScoreBoard();
	}
}

void display::main(){
	for(;;){
		auto event = wait(newBulletFlag+newMagazineFlag+newHealthFlag+/*newScoreBoardFlag+*/newTimeFlag+newPowerUpFlag);
		if(event == newBulletFlag){
			hwlib::cout<<"Ik ben hier :)";
			HWLIB_TRACE;

			drawBullets(false);
		} else if (event == newMagazineFlag){
			hwlib::cout<<"Ik ben hier :)";
			HWLIB_TRACE;

			drawMagazines(false);
		} else if (event == newHealthFlag){
			hwlib::cout<<"Ik ben hier :)";
			HWLIB_TRACE;

			updateHealth();
		} else if (event == newTimeFlag){
			hwlib::cout<<"Ik ben hier :)";
			HWLIB_TRACE;

			drawTime();
		} else if (event == newPowerUpFlag){
			hwlib::cout<<"Ik ben hier :)";
			HWLIB_TRACE;

			drawPowerUp();
		} /*else if (event == newScoreBoardFlag){

		} */
	}
}
