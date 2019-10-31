#include "mp3.hpp"
send::send( hwlib::pin_out & mp3Reset, hwlib::pin_out & mp3Write ):
	mp3Reset( mp3Reset ),
	mp3Write( mp3Write )
{ init(); }

void send::init(){ mp3Reset.write(0); mp3Write.write(0);}
void send::reset(){ mp3Reset.write( 1 ); }
void send::write(){ mp3Write.write( 1 );mp3Write.write( 0 ); }

mp3::mp3( hwlib::pin_out & mp3Reset, hwlib::pin_out & mp3Write ):
	send(  mp3Reset, mp3Write )
{}

void mp3::playSound( int sound ){ 
	reset();								// We can't specify a track, so we start from the first and shift to the specified track
	
	for( int i=1; i<sound; i++){			// Shift to the next track.
		write();	
		
	}
	init();
}			

//void mp3Control::dataReceived( uint32_t data, sounds select ){ //Pseudocode ; Read data from the transceiver and play the right sound
	
//	if(data == select[shot/death/win/lose/powerup]){ 
//		startSound( play(select[shot/death/win/lose/powerup]) );
//	}

//}				