#ifndef __ROTARYENCODER_HPP
#define __ROTARYENCODER_HPP

#include "invoer.hpp"
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

class rotaryEncoder {
	private:
	   	hwlib::target::pin_in CLK = hwlib::target::pin_in( hwlib::target::pins::d40 );
	    hwlib::target::pin_in DT = hwlib::target::pin_in( hwlib::target::pins::d38 );
	    hwlib::target::pin_in SW = hwlib::target::pin_in( hwlib::target::pins::d36 );
	    int posCounter;
	    bool swPress;
	    int lastPos;
	    int curPos;

	    encoderListener * listener;
  	public:
	    rotaryEncoder(encoderListener * listener, const int posCounter = 0, const bool swPress = false);
	    void update();
	    int getPos();
	    void setPos(const int newPos);
	    bool isPressed();

	    bool testCorrectFunctioning();
};

#endif //__ROTARYENCODER_HPP