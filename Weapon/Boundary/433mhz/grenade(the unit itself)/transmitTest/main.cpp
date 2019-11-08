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

   auto spi_bus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(           //creates a SPI object
      sclk, mosi, miso );

   uint8_t transmitAddress[5] = { 0, 0, 0, 0, 1 };             //the address we are going to use to transmit data
	   uint8_t receiveAddress[5] = { 0, 0, 0, 0, 101 };             //the address we are going to use to transmit data


   auto nrf = NRF24( spi_bus, ce, csn );                              //creates a nrf24l01+ object
   nrf.start();                                                       //set default values into the register of the rf chip
   nrf.read_pipe(receiveAddress);                                        //sets the pipe, address and payload size
   nrf.powerUp_rx();                        //starts tx mode

   //uint8_t value[5] = { 12, 1, 50, 0, 0 };                              //the value we are going to transmit
   uint8_t len = 5;                                                   //the length of the value in bytes
                                                         //infinity loop
   //nrf.write( value, len );                                        //transmitting data

   //hwlib::wait_ms(10000);

   uint8_t newValue[5] = { 13, 1, 50, 0, 0 }; 
   uint8_t received[5] = { 0, 0, 0, 0, 0 };
   hwlib::cout<<"Start\n";
   for(;;){
	   if( nrf.checkRXfifo() ){
		  
		  hwlib::cout<<"read\n";
		  nrf.read(received, len);
		  nrf.flush_rx();
		 
		  if( received[0] == 12 ){
			  hwlib::cout<<"write\n";
			  nrf.write_pipe( transmitAddress );                                         //sets the pipe, address and payload size
			  nrf.powerDown_rx(); 

			  nrf.write(newValue, len);
			 hwlib::wait_ms(2000);
			  
		 }
	  }
	  
   }
}