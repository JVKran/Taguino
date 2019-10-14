#ifndef _PAUSE_LISTENER_HPP
#define _PAUSE_LISTENER_HPP

#include "rtos.hpp"

class pause_listener{
private:


public:

	virtual void pause_detected( int n ) = 0;

};

#endif //_PAUSE_LISTENER_HPP