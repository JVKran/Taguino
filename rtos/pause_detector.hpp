#ifndef _PAUSE_DETECTOR_HPP
#define _PAUSE_DETECTOR_HPP

#include "pause_listener.hpp"
#include "msg_decoder.hpp"
#include "msg_listener.hpp"
#include "hwlib.hpp"
#include "rtos.hpp"

class pause_detector : public rtos::task<>, public pause_listener{
private:

	hwlib::pin_in & pin;
	rtos::channel< int, 1024 > pauses;

	pause_listener listener;

public:

	pause_detector( pause_listener listener ):
		listener( listener )
	{}

};

#endif //_PAUSE_DETECTOR_HPP