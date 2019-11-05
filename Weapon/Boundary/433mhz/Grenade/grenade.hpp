#ifndef _GRENADE_HPP
#define _GRENADE_HPP

#include "rtos.hpp"
#include <array>
#include "hwlib.hpp"
#include "input.hpp"

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
class buttonListener {
	public:
		virtual void buttonPressed(const char id) = 0;
};


class button{
private:
	hwlib::target::pin_in sw = hwlib::target::pin_in( hwlib::target::pins::d4);
	buttonListen* listener;
public:
	button( buttonListen * listener );
	void update();
};
*/

class mhz433Read : public mhzListener, public rtos::task<>, public hwuart{
private:
	rtos::clock sampleClock;
	
	std::array< mhzListener*, 5> listenMhz;
	int amountMhzListeners = 0;
	
	const int amount = 4;
	
public:
	mhz433Read( long long int duration );
	
	void addMhzListener( mhzListener * listener );
	
	void dataReceived( const uint8_t data[], const int len ) override;
	
	void read();
	
	void main() override;
	
};

class mhz433Write : public inputHandler, public buttonListener, public hwuart{
private:
	//rtos::clock updateClock;
	rtos::flag buttonFlag;
	
	uint8_t player;
	uint8_t damage;
	
	buttonListener * butt;
	inputHandler * input;
	button b = button(input, butt, 1);
	
	
	const int amount = 4;
	enum class states{ IDLE, WRITE };
	states state;
	
	
public:
	mhz433Write( uint8_t player, uint8_t damage );
	
	void buttonPressed(const char id)override;
	
	void write( uint8_t playerNumber, uint8_t damage );
	//uint8_t dmgTimer( uint8_t damage );
	
	void main() override;
}; 

#endif // GRENADE_HPP