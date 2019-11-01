#include <array>
#include "hwlib.hpp"

#define startByte 0x7E//126
#define versionByte 0xFF//255
#define commandLength 0x06//6
#define endByte 0xEF//239
#define acknowledge 0x01//0
/*
template< int N >
class sounds{
private:
	std::array<int, N> sound;
public:
	int play( int i ){ return sound[ i-1 ]; }
	void set( int setSound ){ sound[setSound-1] = setSound; }

};
*/
class hwuart{
	//Usart * hw_usart = USART0;
	public:
	hwuart();
	bool usart_char_available();
	char usart_getc();
	void usart_putc(char c);
};
