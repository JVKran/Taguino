#include "mp3.hpp"
send::send(hwlib::pin_out & mp3Transmit, hwlib::pin_in & mp3Receive):
	mp3Transmit( mp3Transmit ),
	mp3Receive( mp3Receive )
{}

bool send::readUart(){ bool b = hwlib::uart_getc_bit_banged_pin( mp3Receive ); return b;  }

//void send::sendBit( bool b ){ mp3Transmit.write( b );}

//void send::sendByte( uint8_t c ){
//	unsigned int mask = 1u << 7;
//	hwlib::cout<<"Start\n";
//	for( int i=0; i<8;i++){	
//			bool bit = ( (c & mask ) ? 1 : 0 );
//			sendBit( bit );
//			c <<=1;
//	};
//}

void send::sendArray( const uint8_t* array, int size ){
	while(size--){
		
		sendUart( *array++ );
		
	};
}

void send::sendUart( uint8_t c ){
	hwlib::cout<< c << "\n";
	hwlib::uart_putc_bit_banged_pin( c, mp3Transmit); 
	hwlib::wait_ms(10);
}

void send::executeCMD( uint8_t CMD, uint8_t par1, uint8_t par2 ){ 		// Command, folder(in numbers 1-99), song(0-255)
	uint16_t checksum = -( versionByte + commandLength + CMD + acknowledge + par1 + par2 ); //Add all and invert it
	uint8_t commandLine[10] = { startByte, versionByte, commandLength, CMD, acknowledge, 
											 par1, par2, uint8_t(checksum >> 8), uint8_t (checksum & 0xFF), endByte }; // checksum shifting to send the first half and the second half as show
	for( uint8_t i = 0; i<10; i++){
		sendUart( commandLine[i] );
	}
}

mp3::mp3( hwlib::pin_out & mp3Transmit, hwlib::pin_in & mp3Receive ):
	send(  mp3Transmit,  mp3Receive )
{}

void mp3::playSound( int sound ){ executeCMD( 3, 1, sound );  }			//0x03 = specify track command, folder 0, number with corresponding mp3 track

void mp3::pauseSound(){ executeCMD( 0x0E, 0, 0 );}					    //Pause

void mp3::setVolume( int volume ){ executeCMD( 6, 0, volume); };		// 6=set volume, nothing, volume range 0-30

void mp3::init(){ executeCMD( 0x3F, 0, 0 );}
//void mp3Control::dataReceived( uint32_t data, sounds select ){ //Pseudocode ; Read data from the transceiver and play the right sound
	
//	if(data == select[shot/death/win/lose/powerup]){ 
//		startSound( play(select[shot/death/win/lose/powerup]) );
//	}

//}				