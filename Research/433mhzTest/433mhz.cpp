#include "433mhz.hpp"
#include "hwlib.hpp"
#include <stdint.h>

transmitter::transmitter(hwlib::pin_out & transmit):
	transmit( transmit )
{}

void transmitter::sendByte( const uint8_t c ){
	for( int i=7; i>0;i--){
		transmit.write(c >> i); 
	}
}

void transmitter::sendArray( const uint8_t* array, int size ){
	while(size--){
		sendByte( *array++ );
	}
}


void transmitter::writeUint( unsigned int val ){
	uint8_t checksum = ( val/256 ) ^ ( val&0xFF );
	sendByte( 0xF0 );									// This gets receiver in sync with the transmitter
	sendArray( g_network_sig, NETWORK_SIG_SIZE);		// g_network_sig contains 3 values, first 2 are used to signify the start, the third allows multiple devices to work in the same area
	sendArray((uint8_t  *)&val, VAL_SIZE);					// Send given value 
	sendByte( checksum );								// Value to check if data is sent corrupted
}

//=========================<receiver>==========================

receiver::receiver(hwlib::pin_in & received):
	received(received)
{}

uint8_t receiver::readByte(){
	uint8_t receivedByte  = 0;
	if(!received.read() == 1){
		for( int i=8; i>0;i--){
			receivedByte |= (!received.read() << i );
			//hwlib::wait_ms(1);
			hwlib::cout<<receivedByte << " : "<<!received.read()<<"\n";
		}
	}
	//hwlib::wait_ms(100);
	//hwlib::cout << !received.read()<< "\n" << receivedByte << hwlib::flush;
	return receivedByte;
}

unsigned int receiver::readUint( bool wait){
	int pos = 0;
	unsigned int val = 0;
	uint8_t  c = 0;
	
	while( pos < NETWORK_SIG_SIZE ){
		c = readByte();
		
		//hwlib::wait_ms(1);
		//hwlib::cout << c << "Ditis CCCC\n";
		if( c == g_network_sig[pos]){
			hwlib::wait_ms(10);
		hwlib::cout<<"In c==g\n";
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

