#include "input.hpp"

button::button(const int pinNumber, inputHandler* handler, buttonListener * listener, const char id, const int buttonNotToBeSet):
	pinNumber(pinNumber),
	listener(listener),
	handler(handler),
	buttonNotToBeSet(buttonNotToBeSet),
	id(id)
{
	buttonsRegister = handler->getRegister();
}

void button::update(){
	if(buttonsRegister->read(pinNumber) && (buttonNotToBeSet == 0 || !buttonsRegister->read(buttonNotToBeSet))){
		listener->buttonPressed(id);
	}
}


//<<<<<<<<<<<<<<<<<<----------------------------------------------------------->>>>>>>>>>>>>>>>>>


inputHandler::inputHandler(unsigned long long int period, const char * name):
	task(name),
	updateClock(this, period, "Update Clock")
{
	buttonsRegister.refreshregister();
}

void inputHandler::addButton(button * b){
	buttons[addedButtons] = b;
	addedButtons++;
}

void inputHandler::addEncoder(KY040 * e){
	encoder = e;
}

buttonRegister * inputHandler::getRegister(){
	return &buttonsRegister;
}

void inputHandler::main(){
	for(;;){
		wait(updateClock);
		buttonsRegister.refreshregister();
		for(int i = 0; i < addedButtons; i++){
			buttons[i]->update();
		}
		encoder->update();
		buttonsRegister.refreshregister();
	}
}