#include "433mhz.hpp"
#include "hwlib.hpp"
#include <stdint.h>

transmitter::transmitter(hwlib::pin_out & transmit):
	transmit( transmit )
{}

void transmitter::sendByte( uint8_t c ){
	unsigned int mask = 1u << 7;
	int digit[8];
	//uint8_t check = c;
	for( int i=8; i>0;i--){
		digit[i] = (c & mask ) ? 1 : 0;
		//hwlib::wait_ms(1);
		//hwlib::cout<< check << " << " << i  << " = "<<c << " :: " << ((c & mask ) ? 1 : 0) << "\n";
		c <<=1;
		transmit.write( digit[i] );
		
	}
}

void transmitter::sendArray( const uint8_t* array, int size ){
	while(size--){
		sendByte( *array++ );
	}
}


void transmitter::writeUint( unsigned int val ){
	uint8_t checksum = ( val/256 ) ^ ( val&0xFF );
	sendByte( 0xF0 );									// This gets receiver in sync with the transmitter (0xF0=240)
	sendArray( g_network_sig, NETWORK_SIG_SIZE);		// g_network_sig contains 3 values, first 2 are used to signify the start, the third allows multiple devices to work in the same area
	sendByte( val);					// Send given value 
	sendByte( checksum );								// Value to check if data is sent corrupted
}

//=========================<receiver>==========================

receiver::receiver(hwlib::pin_in & received):
	received(received)
{}

uint8_t  receiver::readByte(){
	uint8_t receivedByte  = 0;
	for( int i=7; i>0;i--){
		receivedByte |= (received.read() << i );
	}
	return receivedByte;
}

unsigned int receiver::readUint( bool wait){
	int pos = 0;
	unsigned int val = 0;
	uint8_t  c = 0;
	
	while( pos < NETWORK_SIG_SIZE ){
		c = readByte();
		
		if( c == g_network_sig[pos]){
			if(pos == NETWORK_SIG_SIZE-1){
				uint8_t checksum;
				val = readByte();
				val +=((unsigned int)readByte ())*256;
				checksum = readByte ();
				if( checksum != (( val/256 ) ^ ( val&0xFF ) )){			// Check if value is corrupted
					pos = -1;
				}
			}
			++pos;
		}
		else if( c == g_network_sig[0] ){
			pos = 1;
		}
		else{
			pos = 0;
			if(!wait){
				return 0xFFFF;
			}
		}
	}
	return val;
}

