/// @file

#include "interface.hpp"

/// \brief
/// Constructor
/// \details
/// This function creates a refrence for display, inputHandler and weaponManager.
/// It also initializes some concurrency mechanisms.
interfaceManager::interfaceManager(display & Display, inputHandler & handler, signUp & signer, game & gameRunner):
	task(5,"intermanagment"),
	Display(Display),
	handler(handler),
	rotaryEncoder(KY040(15, this, &handler)),
	signer(signer),
	gameRunner(gameRunner),
	encoderPressedFlag(this),
	resetPositionFlag(this),
	newPositionFlag(this),
	positionPool("New Position Pool")
	//toetsenbord(&signer)
{
	handler.addEncoder(&rotaryEncoder);
	//handler.addkeypad(&toetsenbord);
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
			newPositionFlag.set();
		} else {
			positionPool.write(pos);
			newPositionFlag.set();
		}
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

		if(event == newPositionFlag){
			currentPosition = positionPool.read();
			//If button is pressed while not currently setting anything; we want to enter settingmode.
			if(!currentlyInSetting&&currentPosition<3){
			 	Display.selectedWindow((currentPosition >= 0) ? currentPosition % 4 : (currentPosition / -1) % 4);
			} else if(!currentlyInSetting){
				

				Display.scoreTerminal << '\f' << currentPosition << hwlib::flush;
			
			}
			else {
				//Else if we're setting anything we want to determine what we're setting and perform actions based on the position.
				// switch(inWhichSetting){
				// 	case 0:
				// 		weapon.newWeaponSelected(currentPosition % 5);		//We have 5 weapons so perform % 5 to create a possibility of 1, 2, 3, 4, 5 as weapon.
				// 		break;
				// }
			}
		} else {
			if((((currentPosition >= 0)&&(currentPosition<3)) ? currentPosition % 4 : (currentPosition / -1) % 4) == 2){
				signer.startGame(100);			//Start a game with duration of 100 * 10 = 1000 seconds
			}
			else if(currentPosition>=0){
				gameRunner.setgametime(currentPosition*10);
			}
			// if(currentlyInSetting){
			// 	Display.selectedSetting(-1);
			// 	rotaryEncoder.setPos(inWhichSetting);
			// } else {
			// 	Display.selectedSetting(currentPosition % 2);				//We have 2 settings; weapon and power-up
			// 	inWhichSetting = currentPosition % 2;
			// }
			// currentlyInSetting = !currentlyInSetting;
		}
	}
}
