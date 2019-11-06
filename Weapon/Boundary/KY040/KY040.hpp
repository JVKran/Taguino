/// @file

#ifndef __KY040_HPP
#define __KY040_HPP

#include "input.hpp"
#include "button.hpp"
#include "hwlib.hpp"

/// \brief
/// Polling KY040 Rotary Encoder Interface
/// \details
/// This is an interface that simplifies the use of the KY040 Rotary Encoder.
/// This class supports updating the position of the encoder and retrieving the
/// state of the pushbutton. Since Interrupts are not supported the update() 
/// function has got to be called at least every 50ms for the readings to 
/// be accurate enough for use.
/// 
///	All supported operations are:
///		- Get Position
///		- Set Position
///		- Get Button State
///		- Update Position and Button
///
/// ~~~~~~~~~~~~~~~{.cpp}
/// auto CLK = hwlib::target::pin_in( hwlib::target::pins::d22 );
/// auto DT = hwlib::target::pin_in( hwlib::target::pins::d24 );
/// auto SW = hwlib::target::pin_in( hwlib::target::pins::d26 );
/// auto button = KY040(CLK, DT, SW);
/// 
/// for(;;){
/// 	button.update();
/// 	hwlib::cout << button.getPos() << hwlib::endl;
/// 	while(button.isPressed()){
/// 		button.update();
/// 		hwlib::wait_ms(5);
/// 		hwlib::cout << "Pressed" << hwlib::endl;
/// 	}
/// }
/// ~~~~~~~~~~~~~~~

class encoderListener;
class inputHandler;

class KY040 {
	private:
	    rotaryDecoder decoder = rotaryDecoder();
	    int switchPinNumber;

	    int posCounter = 0;
	    int lastPos = 0;

	    encoderListener * listener;

	    inputHandler * handler;
	    buttonRegister * buttonsRegister;
  	public:
	    KY040(const int receivedSwitchPinNumber, encoderListener * listener, inputHandler* handler);
	    
	    void update();

	    int getPos();
	    void setPos(const int newPos);
};

#endif //__KY040_HPP