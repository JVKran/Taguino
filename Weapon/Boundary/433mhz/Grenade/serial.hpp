#include <array>
#include "hwlib.hpp"
//#include "mp3.hpp"

class hwuart{
	//Usart * hw_usart = USART0;
	public:
	hwuart();
	bool usart_char_available();
	char usart_getc();
	void usart_putc(char c);
};

class mhz433 : public hwuart{
private:
	const int amount = 5;
public:
	void write( uint8_t player, uint8_t damage );
	void read();
	
	
};
