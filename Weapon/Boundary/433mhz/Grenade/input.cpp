#include "input.hpp"

button::button( inputHandler* handler, buttonListener * listener, const char id):
	listener(listener),
	handler(handler),
	id(id)
{
}

void button::update(){
	if( !sw.read() ){
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
								hwlib::cout<<"handler\n";
		for(int i = 0; i < addedButtons; i++){
			buttons[i]->update();
		}
	}
}