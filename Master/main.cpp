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

   uint8_t address[5] = { 0x00, 0x00, 0x00, 0x00, 0x00 };
   uint8_t adresses[5][5] = { { 0x00, 0x00, 0x00, 0x00, 0x00 },
   							  { 0x00, 0x00, 0x00, 0x00, 0x00 },
   							  { 0x00, 0x00, 0x00, 0x00, 0x00 },
   							  { 0x00, 0x00, 0x00, 0x00, 0x00 },
   							  { 0x00, 0x00, 0x00, 0x00, 0x00 } 	
	};
   uint8_t countPlayers = 0;
   bool check = true;

   auto nrf = NRF24( spi_bus, ce, csn );                          
   nrf.start();                                                   
   nrf.read_pipe( 0, address );                                
   nrf.rx_mode( 0 );                                                   

   uint8_t value[5] = {};                                         
   uint8_t len = 5;                                              

   for(;;){                                                           
      if( nrf.checkRXfifo() ){                                     
         nrf.read( value, len );                                    

         hwlib::cout << "values: " << hwlib::flush;                 

         for(int i = 0; i < len; i++){                             
            hwlib::cout << value[i] << " " << hwlib::flush; 
            if( value[i] != address[i] ){
            	check = false;
            }      
         }

         if( check == true ){
         	countPlayers++;
         	adresses[countPlayers][4] = countPlayers;

         	nrf.read_pipe( countPlayers, addresses[countPlayers] );
         	nrf.write_pipe( 0, addresses[countPlayers] );
         	nrf.tx_mode( 0 );
         	nrf.write( addresses[countPlayers], len );

         	nrf.rx_mode( 0 );
         }

         hwlib::cout << "\n" << hwlib::flush;                        

         nrf.flush_rx();  
         nrf.flush_tx();                                           
         
      }                                  
   }

}