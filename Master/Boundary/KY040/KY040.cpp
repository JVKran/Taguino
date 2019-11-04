/// @file

#include "KY040.hpp"

/// \brief
/// Constuctor
/// \details
/// This constructor has two mandatory parameters; the CLK and DT pin. Without these pins
/// it is impossible to determine the position of the rotary encoder. The SW doesn't have
/// to be connected; it then always returns 0. 
KY040::KY040(const int receivedSwitchPinNumber, encoderListener * listener, inputHandler* handler): 
	listener(listener)
{
	switchPinNumber = receivedSwitchPinNumber;
	buttonRegister = handler->getRegister();
}

/// \brief
/// Update readings
/// \details
/// This function determines the position of the encoder and checks wether the button is
/// pressed. Since Rotary Encoders are completely time-based, this function has got to be
/// called frequently enough for the values to be updated correctly (~10ms / ~80ms). The
/// Rotary Encoder outputs a grey-code and this function tries to interpret that outputted
/// code. It's very basic though.
void KY040::update(){
	posCounter = encoder.read();
	if(posCounter != lastPos){
		lastPos = posCounter;
		listener->encoderTurned(posCounter);
	}
	if(buttonRegister->read(switchPinNumber)){
		listener->buttonPressed();
	}
}

/// \brief
/// Get Position
/// \details
/// This function returns the current position of the encoder. For the value to be recent,
/// the update() function has got to be called often enough. Positions can be both, 
/// negative (counter clockwise) and positive (clockwise).
int KY040::getPos(){
	return posCounter;
}

/// \brief
/// Set Position
/// \details
/// This function can be used to set the position to a desired value. This way a new zero-
/// point can be selected. Positions can be both, negative (counter clockwise) and positive (clockwise).
void KY040::setPos(const int newPos){
	posCounter = newPos;
}
