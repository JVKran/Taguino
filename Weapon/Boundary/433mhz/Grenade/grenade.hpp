#ifndef _GRENADE_HPP
#define _GRENADE_HPP

#include "rtos.hpp"
#include <array>
#include "hwlib.hpp"

class hwuart{
	//Usart * hw_usart = USART0;
	public:
	hwuart();
	bool char_available();
	char getc();
	void putc(char c);

};

class buttonListener{
public:
	buttonPressed( button b );
}

class button{
private:
	hwlib::pin_in & sw;
	std::array< buttonListener*, 1> buttonListener;
public:
	button( hwlib::pin_in & sw );
	void addButtonListener( buttonListener* );
}

class mhzListener{
public:
	virtual void dataReceived( const uint8_t data[], const int len )=0;
}

class mhz433 : public hwuart, public rtos::task<>{
private:
	rtos::clock sampleClock;
	
	std::array< mhzListener*, 5> mhzListener;
	const int amountOfListeners = 0;
	
	const int amount = 5;
	uint16_t player = 12345;
	uint8_t damage = 20;
	
public:
	mhz433( hwlib::pin_in & sw, const long long int duration );
	
	void write( uint8_t playerNumber, uint8_t damage );
	void read();
	uint8_t dmgTimer( uint8_t damage );
	
	void addListener( mhzListener * listener );
	void main () override;
	
};

#endif // GRENADE_HPP