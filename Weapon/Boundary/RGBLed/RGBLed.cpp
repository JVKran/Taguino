/// @file

#include "hwlib.hpp"
#include "RGBLed.hpp"

/// \brief
/// Constructor
/// \details
/// This constructor takes one pin_out and one pin_in. These are the trig_pin and
/// echo_pin respectively.
RGBLed::RGBLed(hwlib::color color):
	currentcolor(color)
{setColor(color);}

void RGBLed::setColor(hwlib::color color){
    currentcolor = color;
    if(color.green>127){
        greenpin.write(0);
    }
    else
    {
        greenpin.write(1);
    }
    
    if(color.red>127){
        redpin.write(0);
    }
    else
    {
        redpin.write(1);
    }

    if(color.blue>127){
        bluepin.write(0);
    }
    else
    {
        bluepin.write(1);
    }
    
}


