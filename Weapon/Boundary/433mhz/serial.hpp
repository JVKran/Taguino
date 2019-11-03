#include <array>
#include "hwlib.hpp"

#define startByte 0x7E//126
#define versionByte 0xFF//255
#define commandLength 0x06//6
#define endByte 0xEF//239
#define acknowledge 0x01//0



class hwuart{
	//Usart * hw_usart = USART0;
	public:
	hwuart();
	bool char_available();
	char getc();
	void putc(char c);
	uint16_t get_uint();
	void put_uint(uint16_t playernumber);
};
