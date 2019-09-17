#include "hwlib.hpp"
#include "transceiver.hpp"

int main( void ){	
   hwlib::wait_ms( 500 );

   //auto irTransmitter = transmitter();
   auto irReceiverPin = hwlib::target::pin_in(hwlib::target::pins::d5);
   auto irReceiver = receiver(irReceiverPin);

   for(;;){
      //irTransmitter.sendChar('c');
      hwlib::cout << irReceiver.readBit() << hwlib::endl;
   }
}
