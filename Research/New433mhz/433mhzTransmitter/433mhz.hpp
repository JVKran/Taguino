#ifndef _433MHZ_HPP
#define _433MHZ_HPP
#include "hwlib.hpp"
#include <stdint.h>

#define NETWORK_SIG_SIZE 3
#define VAL_SIZE 2
#define CHECKSUM_SIZE 1
#define NET_ADDR 5

const uint8_t g_network_sig[NETWORK_SIG_SIZE] { 0x8F, 0xAA, NET_ADDR }; //143, 170, 5

//Testnamen
class transmitter{
private:
	hwlib::pin_out & transmit;
public:
	transmitter( hwlib::pin_out & transmit );
	
	void sendBit(const bool s, unsigned int wait);
	
	void sendByte( uint8_t c );
	
	void sendArray( const uint8_t * array, int size );
	
	void writeUint( unsigned int val );
};

class receiver{
private:
	hwlib::pin_in & received;
public:
	receiver( hwlib::pin_in & received );
	
	uint8_t readByte( bool state );
	
	unsigned int readUint( bool wait );
};
#endif //433MHZ_HPP