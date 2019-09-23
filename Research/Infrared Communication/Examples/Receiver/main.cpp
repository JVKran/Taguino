#include "hwlib.hpp"
#include "transceiver.hpp"

int main( void ){	
   hwlib::wait_ms( 500 );

   auto irReceiverPin = hwlib::target::pin_in(hwlib::target::pins::d5);
   auto irReceiver = receiver(irReceiverPin);

   for(;;){
      if(irReceiver.dataAvailable()){
         hwlib::cout << irReceiver.readChar() << hwlib::endl;
      }
   }
}
