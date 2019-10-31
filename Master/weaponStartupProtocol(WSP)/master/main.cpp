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

   uint8_t address0[5] = { 0x00, 0x00, 0x00, 0x00, 0x00 };

   uint8_t addresses[5][5] = { { 0x00, 0x00, 0x00, 0x00, 0x00 },
   							       { 0x00, 0x00, 0x00, 0x00, 0x00 },
   							       { 0x00, 0x00, 0x00, 0x00, 0x00 },
   							       { 0x00, 0x00, 0x00, 0x00, 0x00 },
   							       { 0x00, 0x00, 0x00, 0x00, 0x00 } 	
	};
   uint8_t countPlayers = 0;
   bool check = true;

   auto nrf = NRF24( spi_bus, ce, csn );                          
   nrf.start();                                                   

   //uint8_t value0[5] = { 1,2,3,4,5 };
   uint8_t value1[5] = {};                                         
   uint8_t len = 5;   

   nrf.read_pipe( 0, address0 );                                
   nrf.rx_mode( 0 );                                          

   for(;;){                                                           
      if( nrf.checkRXfifo() ){                                     
         nrf.read( value1, len );                                    

         hwlib::cout << "\nvalues: " << hwlib::flush;                 

         for(int i = 0; i < len; i++){                             
            hwlib::cout << value1[i] << " " << hwlib::flush;     
         }

         if( value1[0] != address0[0] ){
               check = false;
         }else{
            for (int i = 1; i < len; ++i){
               if(value1[i] != address0[i]){
                  check = false;
               }
            }
         }  

         if( check == true ){
            if(countPlayers > len-1){
               countPlayers = 0;
            }
            hwlib::wait_ms(100);
            countPlayers++;
         	addresses[countPlayers-1][0] = countPlayers;

            hwlib::cout << "\ncreating new player: " << countPlayers << hwlib::endl;

            for (int i = 0; i < len; ++i){
               hwlib::cout << addresses[countPlayers-1][i] << " ";
            }

         	nrf.write_pipe( 0, address0 );
         	nrf.tx_mode( 0 );
         	nrf.write( addresses[countPlayers-1], len );

            nrf.read_pipe( countPlayers, addresses[countPlayers-1] );
         	nrf.rx_mode( countPlayers );

         }                       

         check = true;                                           
         
      }                                 
   } 

}