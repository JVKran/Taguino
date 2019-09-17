#include "hwlib.hpp"
#include "transceiver.hpp"

int main( void ){	
   hwlib::wait_ms( 500 );

   //auto irTransmitter = transmitter();
   auto irReceiverPin = hwlib::target::pin_in(hwlib::target::pins::d5);
   auto irReceiver = receiver(irReceiverPin);

   for(;;){
      if(irReceiver.dataAvailable()){
      //irTransmitter.sendChar('c');
      hwlib::cout << irReceiver.readChar() << hwlib::endl;
      }
      }
}
