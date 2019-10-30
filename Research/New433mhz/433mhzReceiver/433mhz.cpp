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
	sendByte( val);										// Send given value 
	sendByte( checksum );								// Value to check if data is sent corrupted
}

//=========================<receiver>==========================

receiver::receiver(hwlib::pin_in & received):
	received(received)
{}

bool receiver::readBit( bool state,  unsigned int timeBit, unsigned int timeOut){
	// Read pulse
	auto start = hwlib::now_us();										// Start houses current time in us
	for(;;){
		auto duration = hwlib::now_us() - start; 						// Duration is current time - start
		if( duration >= timeOut ){ return !state; }					// If the timeout is reached return negative state
		if( received.read() == state ){									// If the read value is state
			if( duration >= timeBit ){ hwlib::cout<<duration<<"\n";return state; }					// If the duration is bigger or equal return state
		}
		received.refresh();
		
	}//hwlib::cout<<duration<<"\n";
};

void receiver::readTest(){
		bool state = readBit( true, 8000, 8005 );
		if( state){		
			bool state2 =readBit( true, 10100, 10105 );
			hwlib::cout<<"start: "<<state << " : "<<state2<<"\n";
			
		}
	
}

uint8_t receiver::readByte(){
	uint8_t receivedByte = 0;											// This will house the sent byte
	if( readBit( true, 3000, 3005 ) ){									// In nano seconds
		hwlib::cout<<"Reading\n";
		//hwlib::wait_us(10000);
		for( int i=8; i>0;i--){
			//auto highDur = hwlib::now_us();
			auto readLoop = readBit( true, 1, 11100 );
			//auto test = receivedByte;
			receivedByte |= (readLoop << (i-1) );						// Shift received data to the left by i, and put in in receivedByte
			//hwlib::cout<<(hwlib::now_us() - highDur)<<"\n";
			hwlib::cout<< readLoop<<"\n";
			//hwlib::wait_ms(15);
			//hwlib::cout<<receivedByte<<"\n";
			//hwlib::cout<< i-1<<" : " <<(lowDur - highDur) <<" : " <<test << " : "<<readLoop << " : "<<(readLoop<<(i-1))<< " : "<<receivedByte<<"\n";
		}
	}
	//hwlib::wait_ms(1);
	
	return receivedByte;
}

unsigned int receiver::readUint( bool wait){
	int pos = 0;
	unsigned int val = 0;
	uint8_t  c = 0;
	
	while( pos < NETWORK_SIG_SIZE ){									// If pos < 3
		c = readByte();											// c has receivedByte, so the sent character
		
		if(c>0){hwlib::cout<<c<<"\n";}
		if( c == g_network_sig[pos]){									// If the sent character is the same as the one in the array, we know we can start
			return 1;
			hwlib::cout<<"In c==g\n";
			if(pos == NETWORK_SIG_SIZE-1){								// Check of het wel de juiste positie is
				uint8_t checksum;
				val = readByte();									// Read value byte
				//val +=((unsigned int)readByte (true))*256;
				checksum = readByte ();								// The value to check if corrupted
				if( checksum != (( val/256 ) ^ ( val&0xFF ) )){			// Check if value is corrupted by using the same formula as in the writeUint()
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

