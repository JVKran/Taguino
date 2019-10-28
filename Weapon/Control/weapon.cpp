#include "weapon.hpp"

weaponManager::weaponManager(inputHandler & handler, runGame & game):
	triggerButton(button(this, 'T', hwlib::target::pin_in(hwlib::target::pins::d12))),
	autoButton(button(this, 'A', hwlib::target::pin_in(hwlib::target::pins::d11))),
	manualButton(button(this, 'M', hwlib::target::pin_in(hwlib::target::pins::d10))),
	handler(handler),
	game(game),
	player(game.getPlayerData()),
	buttonsChannel(this, "Pressed Buttons Channel")
{
	handler.addButton(&triggerButton);
	handler.addButton(&autoButton);	
	handler.addButton(&manualButton);	
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
				hwlib::cout << "Distance: " << distanceSensor.getDistance() << "cm" << hwlib::endl;
				break;
			case 'A':
				hwlib::cout << "Autofire-Mode selected" << hwlib::endl;
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