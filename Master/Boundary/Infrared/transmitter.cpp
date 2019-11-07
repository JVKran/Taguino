#include "transmitter.hpp"


infraredTransmitter::infraredTransmitter(const long long int period):
   task(1, "Infrared Transmitting Task"),
   transmitClock(this, period, "Transmitting Clock"),
   messageChannel(this, "Message Channel")
{}

void infraredTransmitter::main(){
   for(;;){
      auto event = wait(transmitClock+messageChannel);
      if(event == messageChannel && state == states::IDLE){
         dataToTransmit = messageChannel.read();
         bitsToSend = 15;
         state = states::COMMUNICATING;
         substate = substates::HIGH_TRANSMITTING;
         previousSubstate = substates::SENDING;
         transmitter.write(1);
         highStartTime = hwlib::now_us();
         highDuration = 2400;
         lowDuration = 2400;
         //hwlib::cout << "Message Received: " << dataToTransmit << hwlib::endl;
         bitsToSend = 15;
         hwlib::cout << hwlib::endl;
      } else if (event == transmitClock && state == states::COMMUNICATING){
         switch(substate){
            case substates::SENDING:
            //hwlib::cout << "Sending Data" << hwlib::endl;
               if(bitsToSend >= 0){
                  if(((dataToTransmit >> bitsToSend) & 1UL) == 1){
                     highDuration = 1600;
                     lowDuration = 800;
                  } else {
                     highDuration = 800;
                     lowDuration = 1600;
                  }
                  transmitter.write(1);
                  highStartTime = hwlib::now_us();
                  previousSubstate = substate;
                  substate = substates::HIGH_TRANSMITTING;
                  bitsToSend--;
               } else {
                  substate = substates::CONTROLLING;
                  controlBits = calculateControlBits(dataToTransmit);
                  bitsToSend = 7;
               }
               break;
            case substates::CONTROLLING:
            //hwlib::cout << "Sending Controlbits" << hwlib::endl;
               if(bitsToSend >= 0){
                  if(((controlBits >> bitsToSend) & 1UL) == 1){
                     highDuration = 1600;
                     lowDuration = 800;
                  } else {
                     highDuration = 800;
                     lowDuration = 1600;
                  }
                  transmitter.write(1);
                  highStartTime = hwlib::now_us();
                  previousSubstate = substate;
                  substate = substates::HIGH_TRANSMITTING;
                  bitsToSend--;
               } else {
                  substate = substates::IDLE;
                  state = states::IDLE;
               }
               break;
            case substates::HIGH_TRANSMITTING:
               if(hwlib::now_us() - highStartTime > highDuration){
                  transmitter.write(0);
                  lowStartTime = hwlib::now_us();
                  substate = substates::LOW_TRANSMITTING;
               }
               break;
            case substates::LOW_TRANSMITTING:
               if(hwlib::now_us() - lowStartTime > lowDuration){
                  substate = previousSubstate;
               }
               break;
            case substates::IDLE:
               break;
         }
      }
   }
}

/// \brief
/// Send uint16_t
/// \details
/// This function transmits the passed uint16_t. It does that by calling startCondition() once and
/// sendBit() sixteen times. After the data has been send, another transaction is started with the
/// calculated control bits.
void infraredTransmitter::sendData(const uint16_t data){
   messageChannel.write(data);
}

/// \brief
/// Calculate Control Bits
/// \details
/// This function calculates the control bits based on the passed data. It consists of 8 bits whose
/// value is equal to the xor of bit 0 and bit 7, bit 1 and bit 8, etc.
uint8_t infraredTransmitter::calculateControlBits(const uint16_t data){
   controlBits = 0;
   for(unsigned int i = 0; i < 8; i++){
      controlBits |= (((data >> i) & 1UL) ^ ((data >> (i + 8)) & 1UL)) << i;
   }
   //hwlib::cout << "Calculated Controlbits: " << controlBits << hwlib::endl;
   return controlBits;
}