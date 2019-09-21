/// @file

#include "transceiver.hpp"

// Een bitwaarde 1 bestaat uit 1600 hoog en 800 laag.
// Een bitwaarde 0 bestaat uit 800 hoog 1600 laag.
void transmitter::sendBit(const bool bit){
      transmitter.write(1);
      hwlib::wait_us(800 * (1 + bit));
      transmitter.write(0);
      hwlib::wait_us(800 * (1 + !bit));
   }
   
void transmitter::sendChar(const char test){
   transmitter.write(1);
   hwlib::wait_us(2400);
   for(int i = 7; i > 0; i--){
      sendBit((test >> i) & 1UL);
   }
}

receiver::receiver(hwlib::target::pin_in & irReceiver):
   irReceiver(irReceiver)
{}

bool receiver::dataAvailable(){
   if(!irReceiver.read()){
      highDuration = hwlib::now_us();
      while(!irReceiver.read()){
         irReceiver.refresh();
      }
      highDuration = hwlib::now_us() - highDuration;
      //If startbit received
      if(highDuration > 1600){
         //First wait until it has become high again. Then this bit transaction is over.
         while(irReceiver.read()){
            irReceiver.refresh();
         }
         return true;
      } else {
         return false;
      }
   } else {
      return false;
   }
}

/// \brief
/// Read Bit
/// \details
/// This function returns true if a 1 is received or false when a 0 is received.
/// It first waits for the signal to become high (which is a low signal from the receiver).
/// If a high signal has been received for more than 800us a 1 has been send; 0 otherwise.
bool receiver::readBit(){
   highDuration = hwlib::now_us();
   while(!irReceiver.read()){
      irReceiver.refresh();
   }
   highDuration = hwlib::now_us() - highDuration;
   return (highDuration > 800) ? true : false;
}

char receiver::readChar(){
   receivedChar = 0;
   for(unsigned int i = 0; i < 7;){
      receivedChar |= (readBit() << i);
      i++;
      lowDuration = hwlib::now_us();
      while(irReceiver.read()){
         irReceiver.refresh();
         if(hwlib::now_us() - lowDuration > 2400){
            break;
         }
      }
   }
   return receivedChar;
}

void receiver::binaryDebugTerminal(){
   for(;;){
      if(!irReceiver.read()){
         highDuration = hwlib::now_us();
         while(!irReceiver.read()){
            irReceiver.refresh();
         }
         highDuration = hwlib::now_us() - highDuration;
         //If startbit received
         if(highDuration > 1600){
            receivedChar = 0;
            for(unsigned int i = 0; i <= 8; i++){
               highDuration = hwlib::now_us();
               while(!irReceiver.read()){
                  irReceiver.refresh();
               }
               highDuration = hwlib::now_us() - highDuration;
               if(highDuration > 800){
                  hwlib::cout << '1';
                  receivedChar |= (1UL << (8 - i));
               } else {
                  hwlib::cout << '0';
               }
               lowDuration = hwlib::now_us();
               while(irReceiver.read()){
                  irReceiver.refresh();
                  if(hwlib::now_us() - lowDuration > 2400){
                     break;
                  }
               }
            }
            hwlib::cout << " = " << receivedChar << " = " << char(receivedChar) << hwlib::endl;
         }
      }
   }
}