#include "grenade.hpp"
#include "hwlib.hpp"

int main(){
	hwlib::wait_ms(500);
	namespace target = hwlib::target;
	auto grenadeSw = target::pin_in( target::pin::d7);
	
    auto mhz = mhz433( grenadeSw );
	
	uint16_t player = 12345;
	uint8_t damage = 20;
	
	// Transmit
	if( !grenadeSw.read() ){
		damage = mhz.dmgTimer(damage);		// When the button is pressed it adds 5 damage every second, up to 50. 
		mhz.write( player, damage );		// This will now loop.
	}
	
	// Receive
	
	mhz.read();						// This will now loop
}