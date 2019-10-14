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
   nrf.read_pipe( address );
   nrf.rx_mode();

   uint8_t value[5] = {};
   uint8_t len = 5;

   for(;;){                                                           
      if( nrf.checkRXfifo() ){                                      //checks if there is something in the RX FIFO
         nrf.read( value, len );                                    //reads the RX FIFO

         hwlib::cout << "values: " << hwlib::flush;                 

         for(int i = 0; i < len; i++){                              //displays every byte 
            hwlib::cout << value[i] << " " << hwlib::flush;       
         }

         hwlib::cout << "\n" << hwlib::flush;

         nrf.flush_rx();                                             //empties the RX FIFO
         
      }                                  
   }

}