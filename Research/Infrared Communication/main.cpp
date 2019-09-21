#include "hwlib.hpp"
#include "transceiver.hpp"

int main( void ){	
   hwlib::wait_ms( 500 );

   auto irReceiverPin = hwlib::target::pin_in(hwlib::target::pins::d5);
   auto irReceiver = receiver(irReceiverPin);

   for(;;){
      if(irReceiver.dataAvailable()){
         for(unsigned int i = 0; i < 8; i++){
            hwlib::cout << irReceiver.readBit();

         }
         hwlib::cout << "\n\n";
      }
   }
}

/*
for(;;){
      if(irReceiverPin.read()){
         hwlib::cout << "1" << hwlib::endl;
         while(irReceiverPin.read()){
            irReceiverPin.refresh();
            hwlib::wait_us(50);
         }
      } else {
         hwlib::cout << "0" << hwlib::endl;
         while(!irReceiverPin.read()){
            irReceiverPin.refresh();
            hwlib::wait_us(50);
         }
      }
   }
*/