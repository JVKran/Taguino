/// @file

#include "input.hpp"

/// \brief
/// Constructor 
/// \details
/// The constructor has several mandatory parameters as defined in the class diagram
button::button(const int pinNumber, inputHandler* handler, buttonListener * listener, const char id, const int buttonNotToBeSet):
	pinNumber(pinNumber),
	listener(listener),
	handler(handler),
	buttonNotToBeSet(buttonNotToBeSet),
	id(id)
{
	buttonRegister = handler->getRegister();
}

/// \brief
/// Update 
/// \details
/// Checks register, if set, call buttonPressed on listener.
void button::update(){
	if(buttonRegister->read(pinNumber) && (buttonNotToBeSet == 0 || !buttonRegister->read(buttonNotToBeSet))){
		listener->buttonPressed(id);
	}
}


//<<<<<<<<<<<<<<<<<<----------------------------------------------------------->>>>>>>>>>>>>>>>>>


/// \brief
/// Constructor
/// \details
/// The constructor has several mandatory parameters for RTOS tasks.
inputHandler::inputHandler(unsigned long long int period, const char * name):
	task(2, name),
	updateClock(this, period, "Update Clock")
{
	buttonInterrupter.refreshregister();
}

/// \brief
/// Add Button 
/// \details
/// Add Button to input handler array with buttons.
void inputHandler::addButton(button * b){
	buttons[addedButtons] = b;
	addedButtons++;
}

/// \brief
/// Add Encoder 
/// \details
/// Add Addencoder to input handler array with encoders.
void inputHandler::addEncoder(KY040 * e){
	encoder = e;
}

/// \brief
/// Add Keypad
/// \details
/// Add Keypad to update.
void inputHandler::addkeypad(T9Keys * t){
	toetsenbord = t;
}

/// \brief
/// Get Register
/// \details
/// Buttons need to know the newest state of the register.
Buttoninterrupter * inputHandler::getRegister(){
	return &buttonInterrupter;
}

/// \brief
/// Main
/// \details
/// Call update on all boundary input objects.
void inputHandler::main(){
	for(;;){
				//HWLIB_TRACE;

		wait(updateClock);

		buttonInterrupter.refreshregister();
		for(int i = 0; i < addedButtons; i++){
			buttons[i]->update();
		}
		encoder->update();
		buttonInterrupter.refreshregister();

		toetsenbord->update();
	}
}