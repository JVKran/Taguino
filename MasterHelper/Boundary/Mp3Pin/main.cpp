#include "mp3.hpp"
#include "hwlib.hpp"
#include <array>

//Als uart niet werkt, io mode gebruiken, veel makkelijker. Adkey1 om te resetten naar eerst lied, daarna met IO 2 verder gaan.
int main(){
	namespace target = hwlib::target;
	
	const int amount=4;
	int JAZZ=1; int SHOT=2; int ACTION=3; int AAAH=4;
	std::array< int, amount > sound = { JAZZ, SHOT, ACTION, AAAH };
	
	auto mp3Reset = target::pin_out( target::pins::d5 );
	auto mp3Write = target::pin_out( target::pins::d6 );
	auto mp3Player = mp3( mp3Reset, mp3Write );
	
	auto sw1 = target::pin_in( target::pins::d4 );
	
	auto songs = sounds<amount>();
	for(const auto&s : sound){
		songs.set( s );
	}
	
	for(;;){
		if( !sw1.read() ){
			mp3Player.playSound( songs.play(SHOT) );
		}
	
	}


}