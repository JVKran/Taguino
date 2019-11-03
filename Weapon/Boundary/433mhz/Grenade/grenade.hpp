#ifndef _GRENADE_HPP
#define _GRENADE_HPP

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

class mhz433 : public hwuart{
private:
	const int amount = 5;
	hwlib::pin_in & sw;
public:
	mhz433( hwlib::pin_in & sw );
	void write( uint8_t playerNumber, uint8_t damage );
	void read();
	uint8_t dmgTimer( uint8_t damage );
	
};

#endif // GRENADE_HPP