#include "hwlib.hpp"
#include "NRF24.hpp"
#include "NRF24_register.hpp"

int main( void ){

	namespace target = hwlib::target;

   auto sclk = target::pin_out( target::pins::d9  );
   auto mosi = target::pin_out( target::pins::d12 );
   auto miso = target::pin_in(  target::pins::d13 );
   auto csn  = target::pin_out( target::pins::d11 );
   auto ce   = target::pin_out( target::pins::d10 );

   hwlib::wait_ms( 100 );

   auto spi_bus = hwlib::spi_bus_bit_banged_sclk_mosi_miso( 
      sclk, mosi, miso );

   uint8_t address[5] = { 0x00, 0x00, 0x00, 0x00, 0x01 };

   auto nrf = NRF24( spi_bus, ce, csn );
   nrf.start();
   nrf.write_pipe( address );
   nrf.tx_mode();

   uint8_t value[5] = {1, 2, 3, 4, 5};
   uint8_t len = 5;

   for(;;){                                                           //infinity loop
      hwlib::wait_ms( 100 );                                          //not necessery, but beter to make sure 
      nrf.write( value, len );                                        //transmitting data
   }

}