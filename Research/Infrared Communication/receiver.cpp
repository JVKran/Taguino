/// @file

#include "receiver.hpp"


/// \brief
/// Constructor
/// \details
/// This constructor has one mandatory parameter; the pin to which the receiver is attached.
infraredReceiver::infraredReceiver(highSignalListener & listener):
   task("Signal Detecting Task"),
   listener(listener),
   sampleClock(this, 100, "Sample Clock")
{}

void infraredReceiver::main(){
   for(;;){
      wait(sampleClock);
      switch(state){
         case states::SIGNAL:
            if(!irReceiver.read()){       //If transmitter is high
               highDuration += 100;
            } else {
               listener.highSignalDetected(highDuration);
               state = states::IDLE;
            }
            break;
         case states::IDLE:
            if(!irReceiver.read()){
               state = states::SIGNAL;
               highDuration = 0;
            }
            break;
      }
   }
}

infraredDecoder::infraredDecoder(messageListener & listener):
   listener(listener),
   highDurations(this, "High Durations Channel")
{}

void infraredDecoder::highSignalDetected(const int highDuration){
   highDurations.write(highDuration);
}

uint8_t infraredDecoder::calculateControlBits(const uint16_t data){
   controlBits = 0;
   for(unsigned int i = 0; i < 8; i++){
      controlBits |= (((data >> i) & 1UL) ^ ((data >> (i + 8)) & 1UL)) << i;
   }
   return controlBits;
}

void infraredDecoder::main(){
   for(;;){
      wait(highDurations);
      highDuration = highDurations.read();
      switch(state){
         case states::IDLE:
            if(highDuration > 2000 && highDuration < 2800){
               state = states::MESSAGE;
               //hwlib::cout << "Startcondition Received" << hwlib::endl;
               receivedBits = 0;
               receivedData = 0;
               amountOfControlBits = 0;
               controlBits = 0;
               receivedControlBits = 0;
            }
            break;
         case states::MESSAGE:
            if(highDuration > 400 && highDuration < 2000){
               receivedData |= (highDuration > 1200) ? (1UL << (15 - receivedBits)) : 0;
               receivedBits++;
               if(receivedBits == 16){
                  state = states::CONTROL;
                  hwlib::cout << receivedData << hwlib::endl;
               }
            } else {
               state = states::IDLE;
               hwlib::cout << "Timed-Out with a highduration of " << highDuration << " and this data: " << receivedData << hwlib::endl;
            }
            break;
         case states::CONTROL:
            if(highDuration > 400 && highDuration < 2000){
               receivedControlBits |= (highDuration > 1200) ? (1UL << (7 - amountOfControlBits)) : 0;
               amountOfControlBits++;
               if(amountOfControlBits == 8){
                  controlBits = calculateControlBits(receivedData);
                  if(controlBits == receivedControlBits){
                     listener.messageReceived(receivedData);
                     state = states::IDLE;
                  } else {
                     state = states::IDLE;
                     //hwlib::cout << "Message: " << receivedData << ", Controlbits: " << receivedControlBits << " which should be " << controlBits << hwlib::endl;
                  }
               }
            } else {
               state = states::IDLE;
               //hwlib::cout << "Message: " << receivedData << ", Controlbits: " << receivedControlBits << " which should be " << controlBits << hwlib::endl;
            }
            break;
      }
   }
}