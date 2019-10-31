#include "display.hpp"

void display::showBullets(int amountOfBullets){
	if(amountOfBullets != lastData.lastBullets && (amountOfBullets < 10 || !maxBulletsDrawn)){
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
	}
	bulletWindow.flush();
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

void display::updateHealth(const unsigned int prevHealth, const unsigned int health){
	int amountOfBlack = 27-((100 - health) * 0.27);
	int amountOfWhite = (100 - health) * 0.27;
	if(prevHealth < health){
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

void display::showMagazines(int amountOfMagazines){
	if(amountOfMagazines != lastData.lastMagazines && (amountOfMagazines < 3 || !maxMagazinesDrawn)){
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

void display::showTime(const double remainingSeconds, const double totalSeconds){
	hwlib::circle(hwlib::xy(10,10), 10).draw(timeWindow);
	double LocationToBeFilled = (1-(remainingSeconds/ totalSeconds)) * 360;
	for(int i = 0;i <LocationToBeFilled; i++){
		if(i < 181){
			hwlib::line(hwlib::xy(10,10), hwlib::xy(xCoordinates.get(i+179) + 10, yCoordinates.get(i+179) + 10)).draw(timeWindow);
		}else{
			hwlib::line(hwlib::xy(10,10), hwlib::xy(xCoordinates.get(i-179) + 10, yCoordinates.get(i-179) + 10)).draw(timeWindow);
		}
	}
	timeWindow.flush();
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