#include "mp3.hpp"
#include "hwlib.hpp"
#include <array>

//Als uart niet werkt, io mode gebruiken, veel makkelijker. Adkey1 om te resetten naar eerst lied, daarna met IO 2 verder gaan.
int main(){
	namespace target = hwlib::target;
	
	const int amount=4;
	int JAZZ=1; int SHOT=2; int ACTION=3; int AAAH=4; int volStandard=15;
	std::array< int, amount > sound = { JAZZ, SHOT, ACTION, AAH };
	
	auto mp3Transmit = target::pin_out( target::pins::d10 );
	auto mp3Receiver = target::pin_in( target::pins::d15);
	auto mp3Player = mp3( mp3Transmit, mp3Receiver );

	auto sw1 = target::pin_in( target::pins::d4 );
	auto sw2 = target::pin_in( target::pins::d5 );
	
	auto songs = sounds<amount>();
	for(const auto&s : sound){
		songs.set( s );
	}
	hwlib::wait_ms(200);
	mp3Player.init();
	hwlib::wait_ms(5000);
	mp3Player.setVolume( volStandard );
	hwlib::wait_ms(5000);
	for(;;){
		if( !sw1.read() ){
			hwlib::cout<<"Play sound\n";
			mp3Player.playSound( songs.play( AAAH ) );	
			
			hwlib::wait_ms(500);
		}
		if( !sw2.read() ){
			hwlib::cout<<"Pause\n";
			mp3Player.pauseSound();
			
			hwlib::wait_ms(500);
		}
		
	
	}


}