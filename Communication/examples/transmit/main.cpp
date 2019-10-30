#include "hwlib.hpp"
#include "NRF24.hpp"
#include "NRF24_register.hpp"

int main( void ){

	namespace target = hwlib::target;

   auto sclk = target::pin_out( target::pins::d9  );                  //the clock for spi
   auto mosi = target::pin_out( target::pins::d12 );                  //master out slave in
   auto miso = target::pin_in(  target::pins::d13 );                  //master in slave out
   auto csn  = target::pin_out( target::pins::d11 );                  //to transmit data
   auto ce   = target::pin_out( target::pins::d10 );                  //sets what kind of mode we are in

   hwlib::wait_ms( 100 );                                             //to make sure everything is on time

   auto spi_bus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(           //the spi_bus we are sending over
      sclk, mosi, miso );

   uint8_t address[5] = { 0x05, 0x02, 0x03, 0x04, 0x05 };             //the address we are using to send data

   auto nrf = NRF24( spi_bus, ce, csn );                              //create a object from NRF24 with the default constructor
   nrf.start();                                                       //initialize the default values that are needed
   nrf.write_pipe( 0, address );                                      //set the address of default 5 bytes to send it to the right user
   nrf.tx_mode( 0 );                                                  //we need to be in tx_mode to be able to transmit

   uint8_t value[5] = {1, 2, 3, 4, 5};                                //the data we are going to transmit
   uint8_t len = 5;                                                   //the amount of bytes we are sending

   //hwlib::cout << nrf.read_register(RX_ADDR_P0) << hwlib::endl;
   //hwlib::cout << nrf.read_register(TX_ADDR) << hwlib::endl;

   for(;;){                                                           //infinity loop
      hwlib::wait_ms( 1000 );                                          //not necessery, but makes sure no value is read wrong, the wait can be shorter if you want
      nrf.write( value, len );                                        //transmitting the data in value with a length of len
      hwlib::cout << "send data" << hwlib::endl;
   }

}