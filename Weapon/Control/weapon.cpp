#include "weapon.hpp"

weaponManager::weaponManager(display & Display, inputHandler & handler, runGame & game, playerData & player):
	task("Weapon managing task"),
	Display(Display),
	triggerButton(button(17, &handler, this, 'T')),
	triggerReleaseButton(button(20, &handler, this, 'R')),
	autoButton(button(18, &handler, this, 'A')),
	burstButton(button(19, &handler, this, 'B')),
	leftManualButton(button(14, &handler, this, 'M', 19)),
	rightManualButton(button(21, &handler, this, 'M', 18)),
	handler(handler),
	game(game),
	player(player),
	shootTimer(this, "Shoot Timer"),
	buttonsChannel(this, "Pressed Buttons Channel")
{
	handler.addButton(&triggerButton);
	handler.addButton(&leftManualButton);
	handler.addButton(&rightManualButton);
	handler.addButton(&autoButton);	
	handler.addButton(&burstButton);
	handler.addButton(&triggerReleaseButton);
	Display.showBullets(weapon.getAmountOfBullets());
	Display.showWeapon(weapon.getId());	
	Display.showMagazines(weapon.getAmountOfMags());
}

void weaponManager::buttonPressed(const char id){
	buttonsChannel.write(id);
}

void weaponManager::newWeaponSelected(const int id){
	weapon.setId(id);
	Display.showWeapon(id);
	autoFireMode = false;
	burstFireMode = false;
	manualFireMode = true;
}

void weaponManager::shootBullet(){
	if(weapon.getAmountOfBullets() > 0 /* && hwlib::now_us() - lastShot > (1'000'000 / (weapon.maxShotsPerTenSeconds() / 10))*/){
		dataToSend = 0;
		dataToSend |= (player.getPlayerNumber() << 10);
		dataToSend |= (weapon.getId() << 6);
		if(hwlib::now_us() - lastShot > 1'000'000){
			measuredDistance = distanceSensor.getDistance();  //Need one more bit so substract the biggest one
			lastShot = hwlib::now_us();
		}
		dataToSend |= (measuredDistance < 500) ? measuredDistance / 10 : 0;
		irTransmitter.sendData(dataToSend);
		hwlib::cout << "Shot fired! Distance: " << measuredDistance << ", Player: " << player.getPlayerNumber() << hwlib::endl;
		weapon.setAmountOfBullets(weapon.getAmountOfBullets() - 1);
	} else/* if (hwlib::now_us() - lastShot > (1'000'000 / (weapon.maxShotsPerTenSeconds() / 10)))*/{
		//hwlib::cout << "Triggerbutton pressed but too little bullets..." << hwlib::endl;
		if(weapon.getAmountOfMags() > 0){
			weapon.setAmountOfMags(weapon.getAmountOfMags() - 1);
			Display.showMagazines(weapon.getAmountOfMags());
			weapon.setAmountOfBullets(weapon.bulletsPerMag());
			//hwlib::cout << "Reloaded Weapon!" << hwlib::endl;
		} else {
			//hwlib::cout << "No magazines left. Weapon unloaded..." << hwlib::endl;
		}
	}
}	

void weaponManager::main(){
	for(;;){
		auto event = wait(buttonsChannel+shootTimer);
		if(event == buttonsChannel){
			readButton = buttonsChannel.read();
			switch(readButton){
				case 'T':
					hwlib::cout << "Triggerbutton Pressed" << hwlib::endl;
					shootTimer.set(100);
					shotBullets = 0;
					triggerPressed = true;
					break;
				case 'A':
					hwlib::cout << "Autofire-Mode selected" << hwlib::endl;
					//if(weapon.autoAllowed()){						//Uitgecomment voor debugdoeleinden; definitieve versie heeft dit wel.
						autoFireMode = true;
						burstFireMode = false;
						manualFireMode = false;
						shotBullets = 0;
					//}
					break;
				case 'B':
					hwlib::cout << "Burstfire-Mode selected" << hwlib::endl;
					//if(weapon.burstAllowed()){					//Uitgecomment voor debugdoeleinden; definitieve versie heeft dit wel.
						autoFireMode = false;
						burstFireMode = true;
						manualFireMode = false;
					//}
					break;
				case 'M':
					hwlib::cout << "Manualfire-Mode selected" << hwlib::endl;
					autoFireMode = false;
					burstFireMode = false;
					manualFireMode = true;
					break;
				case 'R':
					hwlib::cout << "Triggerbutton Released" << hwlib::endl;
					Display.showBullets(weapon.getAmountOfBullets());
					hwlib::cout << "Kogels: " << weapon.getAmountOfBullets() << hwlib::endl;
					triggerPressed = false;
					break;
				default:
					hwlib::cout << "Unknown button pressed?" << hwlib::endl;
					break;
			}
		} else {
			if(manualFireMode){
				shootBullet();
			} else if(burstFireMode && triggerPressed){
				if(shotBullets < 5){
					shotBullets++;
					shootBullet();
					shootTimer.set(100'000);			//Dit moet vervangen worden door "weapon.getMaxShotsPerTenSeconds() / 10"
				}
			} else if(autoFireMode && triggerPressed){
				shootBullet();
				shootTimer.set(100'000);				//Dit moet vervangen worden door "weapon.getMaxShotsPerTenSeconds() / 10"
			}
		}
	}
}