#include "weapon.hpp"

weaponManager::weaponManager(inputHandler & handler):
	triggerButton(button(this, 'T', hwlib::target::pin_in(hwlib::target::pins::d12))),
	autoButton(button(this, 'A', hwlib::target::pin_in(hwlib::target::pins::d11))),
	handler(handler)
{
	handler.addButton(&triggerButton);
	handler.addButton(&autoButton);
}

void weaponManager::buttonPressed(const char id){
	hwlib::cout << "Button " << id << " Pressed!" << hwlib::endl;
}