#include "playerData.hpp"
#include "hwlib.hpp"
#include "NRF24.hpp"

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

   uint8_t address[5] = { 0x05, 0x04, 0x03, 0x02, 0x01 };

   auto nrf = NRF24( spi_bus, ce, csn );                          
   nrf.start();                                                   
   nrf.read_pipe( 3, address );                                
   nrf.rx_mode( 3 );                                                   

   uint8_t value[5] = {};                                         
   uint8_t len = 5;                                              

   for(;;){                                                           
      if( nrf.checkRXfifo() ){                                     
         nrf.read( value, len );                                    

         hwlib::cout << "values: " << hwlib::flush;                 

         for(int i = 0; i < len; i++){                             
            hwlib::cout << value[i] << " " << hwlib::flush;       
         }

         hwlib::cout << "\n" << hwlib::flush;                        

         nrf.flush_rx();                                             
         
      }                                  
   }

}