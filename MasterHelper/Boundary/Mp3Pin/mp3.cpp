#include "mp3.hpp"
send::send()
mp3::mp3( hwlib::pin_out & mp3Transmit, hwlib::pin_in & mp3Receive ):
	send(  mp3Transmit,  mp3Receive )
{}

void mp3::playSound( int sound ){ 
	Reset.write(1); 
	hwlib::wait_ms(1);
	for( int i=0; i<sound; i++)
								}			//0x03 = specify track command, folder 0, number with corresponding mp3 track

//void mp3Control::dataReceived( uint32_t data, sounds select ){ //Pseudocode ; Read data from the transceiver and play the right sound
	
//	if(data == select[shot/death/win/lose/powerup]){ 
//		startSound( play(select[shot/death/win/lose/powerup]) );
//	}

//}				