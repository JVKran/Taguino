#include "weapon.hpp"

weaponManager::weaponManager(display & Display, inputHandler & handler, runGame & game):
	Display(Display),
	triggerButton(button(17, &handler, this, 'T')),
	autoButton(button(18, &handler, this, 'A')),
	manualButton(button(19, &handler, this, 'M')),
	handler(handler),
	game(game),
	player(game.getPlayerData()),
	buttonsChannel(this, "Pressed Buttons Channel")
{
	handler.addButton(&triggerButton);
	handler.addButton(&autoButton);	
	handler.addButton(&manualButton);
	Display.showBullets(weapon.getAmountOfBullets());
	Display.showWeapon(weapon.getId());	
	Display.showMagazines(weapon.getAmountOfMags());
}

void weaponManager::buttonPressed(const char id){
	buttonsChannel.write(id);
}

void weaponManager::main(){
	for(;;){
		wait(buttonsChannel);
		readButton = buttonsChannel.read();
		switch(readButton){
			case 'T':
				if(weapon.getAmountOfBullets() > 0){
					dataToSend = 0;
					dataToSend |= (player.getPlayerNumber() << 10);
					dataToSend |= (weapon.getId() << 6);
					if(hwlib::now_us() - lastShot > 1'000'000){
						measuredDistance = distanceSensor.getDistance();
						lastShot = hwlib::now_us();
					}
					dataToSend |= measuredDistance;
					irTransmitter.sendData(dataToSend);
					hwlib::cout << "Shot fired! Distance: " << measuredDistance << hwlib::endl;
					weapon.setAmountOfBullets(weapon.getAmountOfBullets() - 1);
					Display.showBullets(weapon.getAmountOfBullets());
				} else {
					hwlib::cout << "Triggerbutton pressed but too little bullets..." << hwlib::endl;
					if(weapon.getAmountOfMags() > 0){
						weapon.setAmountOfMags(weapon.getAmountOfMags() - 1);
						Display.showMagazines(weapon.getAmountOfMags());
						weapon.setAmountOfBullets(weapon.bulletsPerMag());
						Display.showBullets(weapon.getAmountOfBullets());
						hwlib::cout << "Reloaded Weapon!" << hwlib::endl;
					} else {
						hwlib::cout << "No magazines left. Weapon unloaded..." << hwlib::endl;
					}
				}
				break;
			case 'A':
				hwlib::cout << "Autofire-Mode selected" << hwlib::endl;
				if(weapon.autoAllowed()){
					
				}
				break;
			case 'M':
				hwlib::cout << "Manual-Mode selected" << hwlib::endl;
				break;
			default:
				hwlib::cout << "Unknown button pressed?" << hwlib::endl;
				break;
		}
	}
}