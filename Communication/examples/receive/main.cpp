#include "hwlib.hpp"
#include "NRF24.hpp"
#include "NRF24_register.hpp"

int main( void ){

   namespace target = hwlib::target;

   auto sclk = target::pin_out( target::pins::d9  );                 //the clock of the SPI
   auto mosi = target::pin_out( target::pins::d12 );                 //master out slave in
   auto miso = target::pin_in(  target::pins::d13 );                 //master in slave out
   auto csn  = target::pin_out( target::pins::d11 );                 //decides when SPI communication starts
   auto ce   = target::pin_out( target::pins::d10 );                 //the pin for the right mode

   hwlib::wait_ms( 100 );                                            //waint 100 ms

   auto spi_bus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(          //the spi_bus
      sclk, mosi, miso );

   uint8_t address[5] = { 0x05, 0x04, 0x03, 0x02, 0x01 };

   auto nrf = NRF24( spi_bus, ce, csn );                             //create a object of NRF24 with default constructor
   nrf.start();                                                      //initialize default things
   nrf.read_pipe( 3, address );                                         //on which pipe we are going to listen
   nrf.rx_mode( 3 );                                                    //go into rx_mode to be able to receive data

   uint8_t value[5] = {};                                            //the array in which we will put the data
   uint8_t len = 5;                                                  //the length of the data

   for(;;){                                                           
      if( nrf.checkRXfifo() ){                                       //checks if there is something in the RX FIFO
         nrf.read( value, len );                                     //reads the RX FIFO

         hwlib::cout << "values: " << hwlib::flush;                 

         for(int i = 0; i < len; i++){                               //displays every byte 
            hwlib::cout << value[i] << " " << hwlib::flush;       
         }

         hwlib::cout << "\n" << hwlib::flush;                        //set an enter after the array

         nrf.flush_rx();                                             //empties the RX FIFO
         
      }                                  
   }

}