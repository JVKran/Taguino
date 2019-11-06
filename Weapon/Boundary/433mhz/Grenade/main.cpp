#include "grenade.hpp"
#include "hwlib.hpp"

int main(){
	hwlib::wait_ms(500);
		
	uint8_t player = 2;
	uint8_t damage = 50;
	
	
	inputHandler handler = inputHandler(100'000);
    auto mhzWrite = mhz433Write( player, damage, &handler );
	rtos::run();
	//auto mhzRead = mhz433Read( 1000 );
	//(//void) mhzRead;
}