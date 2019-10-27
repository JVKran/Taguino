#include "input.hpp"

button::button(buttonListener * listener, const char id, hwlib::target::pin_in buttonPin):
	buttonPin(buttonPin),
	listener(listener),
	id(id)
{}

void button::update(){
	buttonPin.refresh();
	if(!buttonPin.read()){
		listener->buttonPressed(id);
	}
}


//<<<<<<<<<<<<<<<<<<----------------------------------------------------------->>>>>>>>>>>>>>>>>>


inputHandler::inputHandler(unsigned long long int period, const char * name):
	task(name),
	updateClock(this, period, "Update Clock")
{}

void inputHandler::addButton(button * b){
	buttons[addedButtons] = b;
	addedButtons++;
}

void inputHandler::main(){
	for(;;){
		wait(updateClock);
		for(int i = 0; i < addedButtons; i++){
			buttons[i]->update();
		}
	}
}