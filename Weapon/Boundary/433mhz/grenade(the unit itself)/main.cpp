#include "grenade.hpp"
#include "hwlib.hpp"
#include "rtos.hpp"

int main(){
	
	hwlib::wait_ms(500);
	
	namespace target = hwlib::target;
		
	uint8_t player = 0;
	uint8_t damage = 50;
	
    auto sclk = target::pin_out( target::pins::d9 );
  	auto mosi = target::pin_out( target::pins::d12 );
   	auto miso = target::pin_in( target::pins::d7 );
   	auto csn  = target::pin_out( target::pins::d11 );
   	auto ce   = target::pin_out( target::pins::d10 );
	
    auto spiBus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(sclk, mosi, miso );
	
	const long long int inputPollPeriod = 100'000;
	const long long int radioPollPeriod = 100'000;
	const uint8_t addressToListenTo = 101;
	
  	NRF24 radio = NRF24(spiBus, ce, csn, radioPollPeriod, addressToListenTo);
	
	mhz433Write mhz = mhz433Write(player, damage);
	
	inputHandler handler = inputHandler(inputPollPeriod);
	
	exchangeGrenadeData grenade = exchangeGrenadeData( radio, mhz, handler );

	radio.addListener(&grenade);
	
	rtos::run();
	
}