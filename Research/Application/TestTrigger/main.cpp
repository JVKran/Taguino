#include "hwlib.hpp"
#include "weaponTrigger.hpp"

int main( void ){	
	hwlib::wait_ms( 500 );

	auto weaponTriggerPin = hwlib::target::pin_in(hwlib::target::pins::d7);
	auto trigger = weaponTrigger(weaponTriggerPin);
   	for(;;){
   		hwlib::cout<<trigger.detectTrigger()<<'\n';
   	}
}
