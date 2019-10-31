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
	newPositionFlag.set();
	positionPool.write(pos);
}

void interfaceManager::main(){
	for(;;){
		hwlib::cout << "InterfaceManaging Task" << hwlib::endl;
		auto event = wait(newPositionFlag+encoderPressedFlag);
		if(event == newPositionFlag){
			currentPosition = positionPool.read();
			hwlib::cout << "Encoder Turned to position " << currentPosition << "." << hwlib::endl;

		} else {
			if(currentlyInSetting){
				Display.selectedSetting(-1);
				weapon.newWeaponSelected(currentPosition / 2);
				rotaryEncoder.setPos(inWhichSetting);
			} else {
				Display.selectedSetting(currentPosition);
				inWhichSetting = currentPosition;
			}
			currentlyInSetting = !currentlyInSetting;
		}
	}
}
