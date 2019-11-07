#ifndef _GRENADE_HPP
#define _GRENADE_HPP

#include "rtos.hpp"
#include <array>
#include "hwlib.hpp"
#include "NRF24.hpp"
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
	virtual void mhzDataReceived( const uint8_t data[], const int len )=0;
};


class mhz433Read : public rtos::task<256>, public hwuart{
private:
	rtos::clock updategraClock;
	
	std::array< mhzListener*, 5> listenMhz;
	int amountMhzListeners = 0;
	
	const int amount = 4;
	
public:
	mhz433Read(unsigned long long int duration=100000, const char * name = "Grenade");
	
	void addMhzListener( mhzListener * listener );
	
	//virtual void mhzDataReceived( const uint8_t data[], const int len );// override;
	
	void read();
	
	void main() override;
	
};

class mhz433Write : public hwuart{
private:
	//rtos::clock updateClock;
	
	uint8_t player;
	uint8_t damage;

	const int amount = 4;

	
	
public:
	mhz433Write( uint8_t player , uint8_t damage );
	
	void write( uint8_t playerNumber, uint8_t damage );
	
	//void main() override;
}; 

class exchangeGrenadeData : public radioListener, public buttonListener, public rtos::task<> {
private:
	NRF24 radio;
	mhz433Write mhz;
	inputHandler handler;
	
	button proximity;
	
	rtos::flag buttonFlag;
	
	uint8_t storedData[5] = { 0, 0, 0, 0, 0 };
	uint8_t receiveAddress[5] = {0, 0, 0, 0, 101};
	bool stop=0;
	
	enum class states{ IDLE, ACTIVE, EXPLODE, END };
	states state;
	
public:
	exchangeGrenadeData( NRF24 & radio, mhz433Write &mhz, inputHandler & handler );
	
	virtual void dataReceived(const uint8_t data[], const int len) override;
	
	virtual void buttonPressed( const char id );
	
	void sendNrf();
	
	void explode( uint8_t player, uint8_t damage);
	
	void main() override;
	

};

#endif // GRENADE_HPP