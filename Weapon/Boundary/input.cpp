#include "input.hpp"

button::button(const int pinNumber, inputHandler* handler, buttonListener * listener, const char id):
	pinNumber(pinNumber),
	listener(listener),
	handler(handler),
	id(id)
{
	buttonRegister = handler->getRegister();
}

void button::update(){
	if(buttonRegister->read(pinNumber)){
		listener->buttonPressed(id);
	}
}


//<<<<<<<<<<<<<<<<<<----------------------------------------------------------->>>>>>>>>>>>>>>>>>


inputHandler::inputHandler(unsigned long long int period, const char * name):
	task(name),
	updateClock(this, period, "Update Clock")
{
	buttonInterrupter.refreshregister();
}

void inputHandler::addButton(button * b){
	buttons[addedButtons] = b;
	addedButtons++;
}

void inputHandler::addEncoder(KY040 * e){
	encoder = e;
}

Buttoninterrupter * inputHandler::getRegister(){
	return &buttonInterrupter;
}

void inputHandler::main(){
	for(;;){
		wait(updateClock);
		buttonInterrupter.refreshregister();
		for(int i = 0; i < addedButtons; i++){
			buttons[i]->update();
		}
		encoder->update();
		buttonInterrupter.refreshregister();
	}
}