#include "input.hpp"

button::button(const int pinNumber, inputHandler* handler, buttonListener * listener, const char id, const int buttonNotToBeSet):
	pinNumber(pinNumber),
	listener(listener),
	handler(handler),
	buttonNotToBeSet(buttonNotToBeSet),
	id(id)
{
	buttonRegister = handler->getRegister();
}

void button::update(){
	if(buttonRegister->read(pinNumber) && (buttonNotToBeSet == 0 || !buttonRegister->read(buttonNotToBeSet))){
		hwlib::cout<<"inup\n";
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
		HWLIB_TRACE;
		wait(updateClock);
		buttonInterrupter.refreshregister();
		for(int i = 0; i < addedButtons; i++){
			buttons[i]->update();
		}
<<<<<<< HEAD
		//encoder->update();
		//buttonInterrupter.refreshregister();
=======
		HWLIB_TRACE;
		//encoder->update();
		HWLIB_TRACE;
		buttonInterrupter.refreshregister();
>>>>>>> b0166c0ea5792a3f16da1955d8db4cf40453034c
	}
}