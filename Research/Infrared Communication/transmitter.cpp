#include "transmitter.hpp"


infraredTransmitter::infraredTransmitter():
   task("Infrared Transmitting Task"),
   transmitClock(this, 100, "Transmitting Clock"),
   messageChannel(this, "Message Channel")
{}

void infraredTransmitter::main(){
   for(;;){
      auto event = wait(transmitClock+messageChannel);
      if(event == messageChannel && state == states::IDLE){
         hwlib::cout << "MessageChannel" << hwlib::endl;
         state = states::COMMUNICATING;
         substate = substates::TRANSMITTING;
         hasBeenControlled = false;
         transmittedDuration = hwlib::now_us();
         highDuration = 2400;
         transmitter.write(1);
         dataToTransmit = messageChannel.read();
         hwlib::cout << "Transmission for data " << dataToTransmit << hwlib::endl;
         bitsToSend = 15;
      } else if (event == transmitClock && state == states::COMMUNICATING){
         hwlib::cout << "TransmitClock" << hwlib::endl;
         switch(substate){
            case substates::CONTROLLING:
               if(hasBeenControlled){
                  state = states::IDLE;
                  break;
               }
               bitsToSend = 7;
               dataToTransmit = calculateControlBits(dataToTransmit);
               hwlib::cout << "Sending controlbits " << int(dataToTransmit) << hwlib::endl;
               hasBeenControlled = true;
               substate = substates::IDLE;
               state = states::IDLE;
               break;
            case substates::IDLE:
               hwlib::cout << "IDLE" << hwlib::endl;
               if(bitsToSend == 0){
                  substate = substates::CONTROLLING;
                  break;
               }
               transmittedDuration = hwlib::now_us();
               transmitter.write(1);
               if((dataToTransmit >> bitsToSend) & 1UL){
                  highDuration = 1600;
                  lowDuration = 800;
               } else {
                  highDuration = 800;
                  lowDuration = 1600;
               }
               substate = substates::TRANSMITTING;
               bitsToSend--;
               break;
            case substates::TRANSMITTING:
               hwlib::cout << "Transmitting" << hwlib::endl;
               if(hwlib::now_us() - transmittedDuration > highDuration){
                  transmitter.write(0);
                  lowTransmittedDuration = hwlib::now_us();
                  substate = substates::NOT_TRANSMITTING;
                  if(highDuration == 2400){
                     hwlib::cout << "Startcondition sent" << hwlib::endl;
                  } else if (highDuration == 1600){
                     hwlib::cout << 0;
                  } else {
                     hwlib::cout << 1;
                  }
               }
               break;
            case substates::NOT_TRANSMITTING:
               hwlib::cout << "NotTrasmitting" << hwlib::endl;
               if(hwlib::now_us() - lowTransmittedDuration > lowDuration){
                  substate = substates::IDLE;
               }
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