#include "mp3.hpp"
#include "hwlib.hpp"
#include <array>
int main(){
	hwlib::wait_ms(4000);
	namespace target = hwlib::target;
	
	auto sw1 = target::pin_in( target::pins::d4 );
	auto sw2 = target::pin_in( target::pins::d5 );	
	
	// Amount of songs on the sd
	const int amount=8;
	
	// Mp3 wacht 4 seconden na het aanroepen van een functie die verzend naar de module
	auto mp3Player = mp3Control<amount>();
	
	// Reset module when starting
	hwlib::cout<<"Reset\n";
	mp3Player.resetModule();
	
	hwlib::cout<<"Set volume\n";
	mp3Player.setVolume( 20 );
	
	hwlib::cout<<"Done\n";
	
	for(;;){
		if( !sw1.read() ){
			hwlib::cout<<"Play sound\n";	
			mp3Player.startPlayingSound( 5 ); // Data van nrf moet hier, er staat nu dummy data
			
		}
		if( !sw2.read() ){
			
			hwlib::cout<<"Pause\n";
			mp3Player.pauseSound();
			
		}
	}
}