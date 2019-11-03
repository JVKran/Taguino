#include "hwlib.hpp"
#include "NRF24.hpp"
#include "NRF24_register.hpp"

int main( void ){

   namespace target = hwlib::target;

   auto sclk = target::pin_out( target::pins::d9 );
   auto mosi = target::pin_out( target::pins::d12 );
   auto miso = target::pin_in( target::pins::d13 );
   auto csn  = target::pin_out( target::pins::d11 );
   auto ce   = target::pin_out( target::pins::d10 );

   hwlib::wait_ms( 100 );

   auto spi_bus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(sclk, mosi, miso );

   uint8_t receiveAddress[5] = { 0, 0, 0, 0, 2 };
   uint8_t transmitAddress[5] = { 0, 0, 0, 0, 1 };

   auto nrf = NRF24( spi_bus, ce, csn );
   nrf.start();
   nrf.write_pipe( transmitAddress );
   nrf.powerDown_rx();

   uint8_t startGameData[5] = { 1, 100, 0, 0, 0 };
   uint8_t startGameLen = 5;

   nrf.write( startGameData, startGameLen );

   nrf.read_pipe( receiveAddress );
   nrf.powerUp_rx();

   uint8_t receivedData[5] = {};
   uint8_t receivedBytes = 5;                                                 //the amount of bytes we will receive
   
   for(;;){                                                         //starts an infinity loop
      
      if( nrf.checkRXfifo() ){                                      //checks if there is something in the RX FIFO
         nrf.read( receivedData, receivedBytes );                                    //reads the RX FIFO

         hwlib::cout << "values: " << hwlib::flush;                 

         for(int i = 0; i < receivedBytes; i++){                              //displays every byte 
            hwlib::cout << receivedData[i] << " " << hwlib::flush;       
         }

         hwlib::cout << "\n" << hwlib::flush;

         nrf.flush_rx();                                             //empties the RX FIFO
         
      }
   }
}