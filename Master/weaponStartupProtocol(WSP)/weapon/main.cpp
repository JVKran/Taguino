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

   uint8_t address0[5] = { 0x00, 0x00, 0x00, 0x00, 0x00 };  
   uint8_t address1[5] = { 0x01, 0x00, 0x00, 0x00, 0x00 };  //write

   auto nrf = NRF24( spi_bus, ce, csn );                          
   nrf.start();                                                                                                      

   uint8_t value0[5] = { 1,2,3,4,5 };
   uint8_t value1[5] = {};                                         
   uint8_t len = 5; 

   //nrf.write_pipe( 0, address0 );                                
   nrf.tx_mode( 0 );
   nrf.write( address0, len );
   hwlib::cout << "create" << hwlib::endl;

   nrf.read_pipe( 0, address0 );
   nrf.rx_mode( 0 );                                              

   for(;;){ 

      //hwlib::cout << "\nnot found yet";                                                          

      if( nrf.checkRXfifo() ){                                     
         nrf.read( value1, len );
         hwlib::cout << "new address: ";

         for (int i = 0; i < len; ++i){
            address1[i] = value1[i]; 
            hwlib::cout << value1[i];
         }
         hwlib::cout << "\n";
         break;
      }                            
   }

   hwlib::cout << "next loop" << "\n";

   nrf.write_pipe( 0, address1 );
   nrf.tx_mode( 0 );

   hwlib::cout << "\nvalue: ";

   for (int i = 0; i < len; ++i){
      hwlib::cout << address1 << " ";
   }

   for(;;){
      hwlib::wait_ms(1000);

      nrf.write( value0, len );
      hwlib::cout << "\nwriting";
   }

}