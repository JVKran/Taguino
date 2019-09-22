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
   transmitter.write(0);
   hwlib::wait_us(2400);
   for(int i = 7; i >= 0; i--){
      sendBit((test >> i) & 1UL);
   }
}

receiver::receiver(hwlib::target::pin_in & irReceiver):
   irReceiver(irReceiver)
{}

/// \brief
/// Data Available
/// \details
/// This function checks if a start condition is currently happening. A start of communication
/// is recognizable by a high signal for 2400us followed by a low signal for 2400us. Since
/// neither a low or high bit is represented this way, it must be the start condition.
bool receiver::dataAvailable(){
   if(!irReceiver.read()){
      highDuration = hwlib::now_us();
      while(!irReceiver.read()){
         irReceiver.refresh();
      }
      highDuration = hwlib::now_us() - highDuration;
      //If startbit received
      if(highDuration > 1600){
         lowDuration = hwlib::now_us();
         while(irReceiver.read()){
            irReceiver.refresh();
         }
         lowDuration = hwlib::now_us() - lowDuration;
         if(lowDuration > 1600){
            return true;
         } else {
            return false;
         }
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
   for(int i = 7; i >= 0; i--){
      lowDuration = hwlib::now_us();
      while(irReceiver.read()){
         irReceiver.refresh();
         if(hwlib::now_us() - lowDuration > 2400){
            return 0;
         }
      }
      highDuration = hwlib::now_us();
      while(!irReceiver.read()){
         irReceiver.refresh();
         hwlib::wait_us(50);
      }
      highDuration = hwlib::now_us() - highDuration;
      if(highDuration > 800){
         receivedChar |= (1UL << i);
      }
   }
   return receivedChar;
}

void receiver::debugTerminal(){
   for(;;){
      if(!irReceiver.read()){
         highDuration = hwlib::now_us();
         while(!irReceiver.read()){
            irReceiver.refresh();
         }
         highDuration = hwlib::now_us() - highDuration;
         //If startbit received
         if(highDuration > 1600){
            lowDuration = hwlib::now_us();
            while(irReceiver.read()){
               irReceiver.refresh();
            }
            lowDuration = hwlib::now_us() - lowDuration;
            if(lowDuration > 1600){
               receivedChar = 0;
               for(int i = 7; i >= 0; i--){
                  while(irReceiver.read()){
                     irReceiver.refresh();
                     hwlib::wait_us(50);
                  }
                  highDuration = hwlib::now_us();
                  while(!irReceiver.read()){
                     irReceiver.refresh();
                     hwlib::wait_us(50);
                  }
                  highDuration = hwlib::now_us() - highDuration;
                  if(highDuration > 800){
                     receivedChar |= (1UL << i);
                  }
               }
               hwlib::cout << int(receivedChar) << " = " << receivedChar << hwlib::endl;
            }
         }
      }
   }
}