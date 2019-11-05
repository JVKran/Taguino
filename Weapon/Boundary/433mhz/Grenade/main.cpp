#include "grenade.hpp"
#include "hwlib.hpp"

int main(){
	hwlib::wait_ms(500);
		
	uint8_t player = 2;
	uint8_t damage = 50;
	
	namespace target = hwlib::target;
	auto grenadeSw = target::pin_in( target::pins::d4);
	
    auto mhzWrite = mhz433Write( grenadeSw, player, damage );
	(void) mhzWrite;
	
	//auto mhzRead = mhz433Read( 1000 );
	//(void) mhzRead;
	rtos::run();

	
}