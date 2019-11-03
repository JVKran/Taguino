#include <array>
#include "hwlib.hpp"
//#include "mp3.hpp"

class hwuart{
	//Usart * hw_usart = USART0;
	public:
	hwuart();
	bool char_available();
	char getc();
	void putc(char c);
	uint16_t get_uint();
};

class mhz433 : public hwuart{
private:
	const int amount = 6;
public:
	void write( uint8_t playerNumber, uint8_t damage );
	void read();
	
	
};
