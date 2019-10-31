#include "interface.hpp"

interfaceManager::interfaceManager(display & Display, inputHandler & handler, weaponManager & weapon):
	Display(Display),
	handler(handler),
	rotaryEncoder(KY040(15, this, &handler)),
	weapon(weapon),
	encoderPressedFlag(this),
	resetPositionFlag(this),
	newPositionFlag(this),
	positionPool("New Position Pool")
{
	handler.addEncoder(&rotaryEncoder);
}

void interfaceManager::buttonPressed(){
	encoderPressedFlag.set();
}

void interfaceManager::encoderTurned(const int pos){
	if(pos%2==0){
		newPositionFlag.set();
		if(pos != 0){
			positionPool.write(pos / 2);
		} else {
			positionPool.write(pos);
		}
	}
}

void interfaceManager::main(){
	for(;;){
		auto event = wait(newPositionFlag+encoderPressedFlag);
		if(event == newPositionFlag){
			currentPosition = positionPool.read();
			hwlib::cout << "Encoder Turned to position " << currentPosition << "." << hwlib::endl;
			if(!currentlyInSetting){
				Display.selectedWindow(currentPosition % 2);
			} else {
				switch(inWhichSetting){
					case 0:
						weapon.newWeaponSelected(currentPosition % 2);
						break;
				}
			}

		} else {
			if(currentlyInSetting){
				Display.selectedSetting(-1);
				weapon.newWeaponSelected(currentPosition);
				rotaryEncoder.setPos(inWhichSetting);
			} else {
				Display.selectedSetting(currentPosition % 2);
				inWhichSetting = currentPosition % 2;
			}
			currentlyInSetting = !currentlyInSetting;
		}
	}
}
