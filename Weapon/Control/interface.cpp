/// @file

#include "interface.hpp"

/// \brief
/// Constructor
/// \details
/// This function creates a refrence for display, inputHandler and weaponManager.
/// It also initializes some concurrency mechanisms.
interfaceManager::interfaceManager(display & Display, inputHandler & handler, weaponManager & weapon):
	Display(Display),
	handler(handler),
	rotaryEncoder(KY040(15, this, &handler)),
	weapon(weapon),
	encoderPressedFlag(this),
	newPositionFlag(this),
	positionPool("New Position Pool")
{
	handler.addEncoder(&rotaryEncoder);
}

/// \brief
/// Encoder Pressed
/// \details
/// This constructor has no mandatory parameters; we only have one Rotary Encoder hence one button to be pressed.
void interfaceManager::buttonPressed(){
	encoderPressedFlag.set();
}

/// \brief
/// Encoder Turned
/// \details
/// This function has one mandatory parameter; the current position.
/// One rotaryEncoder step creates two pulses; hence we only want to know when the position is even.
/// Then, we want to divide that by two to simulate a 0, 1, 2, 3 steppattern when in reality it would be 0, 2, 4, 6, etc.
void interfaceManager::encoderTurned(const int pos){
	if(pos%2==0){
		if(pos != 0){
			positionPool.write(pos / 2);
		} else {
			positionPool.write(pos);
		}
		newPositionFlag.set();
	}
}

/// \brief
/// Interface Managing Task
/// \details
/// This task has a main() which is responsible for handling user input. For example, when the position % 2 == 1
/// the weapon is being selected. Then, when the encoder is turned, another weapon is chosen.
/// A function is then called to change the weapon.
void interfaceManager::main(){
	for(;;){
		auto event = wait(newPositionFlag+encoderPressedFlag);
		switch(state){
			case states::IDLE:
				if(event == newPositionFlag){
					currentPosition = positionPool.read();
					Display.selectedWindow((currentPosition >= 0) ? currentPosition % 2 : (currentPosition / -1) % 2);
				} else {
					state = states::SETTING;
					inWhichSetting = currentPosition % 2;
					Display.selectedSetting(currentPosition % 2);
				}
				break;
			case states::SETTING:
				if(event == newPositionFlag){
					currentPosition = positionPool.read();
					if(currentPosition>0){
						weapon.newWeaponSelected(currentPosition % 5);		//We have 5 weapons so perform % 5 to create a possibility of 1, 2, 3, 4, 5 as weapon.
					}else{
						weapon.newWeaponSelected((currentPosition % 5)/-1);
					}
				} else {
					state = states::IDLE;
					Display.selectedSetting(-1);
					rotaryEncoder.setPos(inWhichSetting);
				}
				break;
		}
	}
}
