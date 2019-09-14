#ifndef __TRANSMITTER_HPP
#define __TRANSMITTER_HPP

#include "hwlib.hpp"

namespace target = hwlib::target;

class infraredLed {
private:
	due::d2_36kHz transmitter = due::d2_36kHz();
public:
	void flush(){}
};

class transmitter{
private:
	infraredLed led = infraredLed();
};

#endif //__TRANSMITTER_HPP