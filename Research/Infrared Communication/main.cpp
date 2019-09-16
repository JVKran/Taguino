#include "hwlib.hpp"
#include "transceiver.hpp"

int main( void ){	
   hwlib::wait_ms( 500 );

   auto ir = transmitter();

   for(;;){
      ir.sendChar('c');
      hwlib::wait_ms(1000);
   }
}
