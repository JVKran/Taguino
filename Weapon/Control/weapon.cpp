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
	semiFireMode = false;
}	

void weaponManager::main(){
	for(;;){
		wait(buttonsChannel);
		readButton = buttonsChannel.read();
		switch(readButton){
			case 'T':
				hwlib::cout << "Triggerbutton Pressed" << hwlib::endl;
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
					//hwlib::cout << "Shot fired! Distance: " << measuredDistance << ", Player: " << player.getPlayerNumber() << hwlib::endl;
					weapon.setAmountOfBullets(weapon.getAmountOfBullets() - 1);
					Display.showBullets(weapon.getAmountOfBullets());
				} else/* if (hwlib::now_us() - lastShot > (1'000'000 / (weapon.maxShotsPerTenSeconds() / 10)))*/{
					//hwlib::cout << "Triggerbutton pressed but too little bullets..." << hwlib::endl;
					if(weapon.getAmountOfMags() > 0){
						weapon.setAmountOfMags(weapon.getAmountOfMags() - 1);
						Display.showMagazines(weapon.getAmountOfMags());
						weapon.setAmountOfBullets(weapon.bulletsPerMag());
						Display.showBullets(weapon.getAmountOfBullets());
						//hwlib::cout << "Reloaded Weapon!" << hwlib::endl;
					} else {
						//hwlib::cout << "No magazines left. Weapon unloaded..." << hwlib::endl;
					}
				}
				break;
			case 'A':
				hwlib::cout << "Autofire-Mode selected" << hwlib::endl;
				// if(weapon.autoAllowed()){
				// 	autoFireMode = true;
				// 	semiFireMode = false;
				// } else {
				// 	autoFireMode = false;
				// }
				break;
			case 'B':
				hwlib::cout << "Burstfire-Mode selected" << hwlib::endl;
				// if(weapon.semiAllowed()){
				// 	semiFireMode = true;
				// 	autoFireMode = false;
				// } else {
				// 	semiFireMode = false;
				// }
				break;
			case 'M':
				hwlib::cout << "Manualfire-Mode selected" << hwlib::endl;
				break;
			case 'R':
				hwlib::cout << "Triggerbutton Released" << hwlib::endl;
				break;
			default:
				hwlib::cout << "Unknown button pressed?" << hwlib::endl;
				break;
		}
	}
}