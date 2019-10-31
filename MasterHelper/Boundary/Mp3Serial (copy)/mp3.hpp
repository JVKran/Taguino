#include <array>
#include "hwlib.hpp"

#define startByte 0x7E//126
#define versionByte 0xFF//255
#define commandLength 0x06//6
#define endByte 0xEF//239
#define acknowledge 0x00//0

template< int N >
class sounds{
private:
	std::array<int, N> sound;
public:
	int play( int i ){ return sound[ i-1 ]; }
	void set( int setSound ){ sound[setSound-1] = setSound; }

};

class send{
private:
	hwlib::pin_out & mp3Transmit;
	hwlib::pin_in & mp3Receive;
public:
	send( hwlib::pin_out & mp3Transmit, hwlib::pin_in & mp3Receive );
	bool readUart();
	//void sendBit(bool b);
	//void sendByte( uint8_t c);
	void sendArray( const uint8_t * array, int size );
	void sendUart( uint8_t c );
	void executeCMD( uint8_t CMD, uint8_t par1, uint8_t par2);
};

class mp3 : public send {
public:
	mp3( hwlib::pin_out & mp3Transmit, hwlib::pin_in & mp3Receive );
	void init();
	void playSound( int sound );
	void pauseSound();
	void setVolume( int volume ); //Van 0-30
};

class hwuart{
	//Usart * hw_usart = USART0;
	public:
	hwuart();
	bool usart_char_available();
	char usart_getc();
	void usart_putc(char c);
};
//Deze klasse is voor wanneer de nrf goed werkt
//class mp3Control : public mp3{
//private:
//	transceiver& transmitter;
//public:
//	void dataReceived( uint32_t data, sounds select );
//};


