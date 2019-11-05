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

class mhzListener{
public:
	virtual void dataReceived( const uint8_t data[], const int len )=0;
};
/*
class buttonListener{
public:
	virtual void buttonPressed()=0;
};

class button{
private:
	hwlib::pin_in & sw;
	buttonListener* listener;
public:
	button( hwlib::pin_in & sw, buttonListener* listener );
	void update();
};
*/
class mhz433Read : public hwuart, public mhzListener, public rtos::task<>{
private:
	rtos::clock sampleClock;
	
	std::array< mhzListener*, 5> listenMhz;
	int amountMhzListeners = 0;
	
	const int amount = 5;
	
public:
	mhz433Read( long long int duration );
	
	void addMhzListener( mhzListener * listener );
	
	void read();
	
	void main() override;
	
};
/*
class mhz433Write : public buttonListener, public rtos::task<>, public hwuart{
private:
	rtos::flag buttonFlag;

	hwlib::pin_in & sw;
	
	uint8_t player;
	uint8_t damage;
	
	button b;
	buttonListener * listener;
	
	const int amount = 5;
	enum class states{ IDLE, WRITE };
	states state;
	
	
public:
	mhz433Write( hwlib::pin_in & sw, uint8_t player, uint8_t damage );
	
	void buttonPressed() override ;
	
	void write( uint8_t playerNumber, uint8_t damage );
	//uint8_t dmgTimer( uint8_t damage );
	
	void main() override;
}; 
*/
#endif // GRENADE_HPP