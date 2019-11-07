/// @file

#include "weapon.hpp"

/// \brief
/// Constructor
/// \details
/// This constructor has some parameters; the display, handler, game, player and transmitter. These are needed
/// according to the class diagram. Furthermore some RTOS objects are created.
weaponManager::weaponManager(display & Display, inputHandler & handler, runGame & game, playerData & player, infraredTransmitter & irTransmitter):
	task(5, "Weapon managing task"),
	Display(Display),
	triggerButton(button(17, &handler, this, 'T')),
	triggerReleaseButton(button(20, &handler, this, 'R')),
	autoButton(button(18, &handler, this, 'A')),
	burstButton(button(19, &handler, this, 'B')),
	leftManualButton(button(14, &handler, this, 'M', 19)),
	rightManualButton(button(21, &handler, this, 'M', 18)),
	handler(handler),
	irTransmitter(irTransmitter),
	game(game),
	player(player),
	shootTimer(this, "Shoot Timer"),
	buttonsChannel(this, "Pressed Buttons Channel"),
	newWeaponFlag(this),
	newWeaponPool("New Weapon Channel")
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

/// \brief
/// Button Pressed
/// \details
/// This function puts the id in the buttonsChannel.
void weaponManager::buttonPressed(const char id){
	buttonsChannel.write(id);
}

/// \brief
/// New Weapon Selected
/// \details
/// This function puts the id in the weaponPool.
void weaponManager::newWeaponSelected(const int id){
	newWeaponPool.write(id);
	newWeaponFlag.set();
}

/// \brief
/// Select New Weapon
/// \details
/// This function prints the right amount of bullets, magazines and weapon.
void weaponManager::selectNewWeapon(){
	weaponId = newWeaponPool.read();
	weapon.setId(weaponId);
	Display.showWeapon(weaponId);
	Display.showMagazines(weapon.getAmountOfMags());
	Display.showBullets(weapon.getAmountOfBullets());
	autoFireMode = false;
	burstFireMode = false;
	manualFireMode = true;
	Display.showFireMode(0);
}

/// \brief
/// Shoot Bullet
/// \details
/// This function shoots the bullet if there are bullets remaining and the required period has been passed. It also measures distance
/// and shoots that.
void weaponManager::shootBullet(){
	if(weapon.getAmountOfBullets() > 0 && hwlib::now_us() - lastShot > (1'000'000 / (weapon.maxShotsPerTenSeconds() / 10))){
		dataToSend = 0;
		dataToSend |= (game.getPlayerData().getPlayerNumber() << 10);
		dataToSend |= (weapon.getId() << 6);
		if(hwlib::now_us() - lastShot > 1'000'000){
			measuredDistance = distanceSensor.getDistance();  //Need one more bit so substract the biggest one
			lastShot = hwlib::now_us();
		}
		dataToSend |= (measuredDistance < 500) ? measuredDistance / 10 : 0;
		irTransmitter.sendData(dataToSend);
		weapon.setAmountOfBullets(weapon.getAmountOfBullets() - 1);
	} else if (hwlib::now_us() - lastShot > (1'000'000 / (weapon.maxShotsPerTenSeconds() / 10))){
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

/// \brief
/// Main
/// \details
/// Waits for shootTimer, newWeaponFlag and buttonsChannel. Based on the event and values
/// actions are taken.
void weaponManager::main(){
	for(;;){
		auto event = wait(buttonsChannel+shootTimer+newWeaponFlag);
		if(event == buttonsChannel){
			readButton = buttonsChannel.read();
			switch(readButton){
				case 'T':
					shootTimer.set(100);
					shotBullets = 0;
					triggerPressed = true;
					break;
				case 'A':
					hwlib::cout << "Autofire-Mode selected" << hwlib::endl;
					if(weapon.autoAllowed()){
						autoFireMode = true;
						burstFireMode = false;
						manualFireMode = false;
						shotBullets = 0;
						Display.showFireMode(1);
					} else {
						Display.showFireMode(0);
					}
					break;
				case 'B':
					hwlib::cout << "Burstfire-Mode selected" << hwlib::endl;
					if(weapon.burstAllowed()){
						autoFireMode = false;
						burstFireMode = true;
						manualFireMode = false;
						Display.showFireMode(2);
					} else {
						Display.showFireMode(0);
					}
					break;
				case 'M':
					hwlib::cout << "Manualfire-Mode selected" << hwlib::endl;
					autoFireMode = false;
					burstFireMode = false;
					manualFireMode = true;
					Display.showFireMode(0);
					break;
				case 'R':
					Display.showBullets(weapon.getAmountOfBullets());
					triggerPressed = false;
					break;
				default:
					hwlib::cout << "Unknown button pressed?" << hwlib::endl;
					break;
			}
		} else if(event == shootTimer){
			if(manualFireMode){
				shootBullet();
			} else if(burstFireMode && triggerPressed){
				if(shotBullets < 5){
					shotBullets++;
					shootBullet();
					shootTimer.set(1'000'000 / (weapon.maxShotsPerTenSeconds() / 10));
				}
			} else if(autoFireMode && triggerPressed){
				shootBullet();
				shootTimer.set(1'000'000 / (weapon.maxShotsPerTenSeconds() / 10));
			}
		} else {
			selectNewWeapon();
		}
	}
}