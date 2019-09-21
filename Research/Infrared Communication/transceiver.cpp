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
   for(int i = 7; i > 0; i--){
      sendBit((test >> i) & 1UL);
   }
}

receiver::receiver(hwlib::target::pin_in & irReceiver):
   irReceiver(irReceiver)
{}

bool receiver::dataAvailable(){
   if(!irReceiver.read()){
      //Wait while the signal remains high. Then return.
      while(!irReceiver.read()){
         hwlib::wait_us(50);
      }
      return true;
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
   while(irReceiver.read() == 1){
      hwlib::wait_us(50);
   }
   highDuration = hwlib::now_us();
   while(irReceiver.read() == 0){
      hwlib::wait_us(50);
   }
   highDuration = hwlib::now_us() - highDuration;
   if(highDuration > 800){
      return true;
   } else {
      return false;
   }
}

char receiver::readChar(){
   receivedChar = 0;
   for(unsigned int i = 0; i < 8; i++){
      receivedChar |= (readBit() << i);
   }
   return receivedChar;
}