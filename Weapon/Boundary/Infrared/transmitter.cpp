/// @file

#include "transmitter.hpp"

/// \brief
/// Constructor
/// \details
/// This constructor has one mandatory parameter; the period to check wheter or not
/// the transmitterPin should change state.
infraredTransmitter::infraredTransmitter(const long long int period):
   task(2, "Infrared Transmitting Task"),
   transmitClock(this, period, "Transmitting Clock"),
   messageChannel(this, "Message Channel")
{}

/// \brief
/// Infrared Transmitting Task
/// \details
/// This main() is responsible for a couple of things. First of all it should be possible to read from the channel
/// that contains the data that has to be transmitted. That should only be possible when it currently isn't transitting anything; state == idle.
/// Otherwise a new messagetransmission would start while the previous one has not been finished.
/// Secondly it should be able to transmit the data. Hence there are four substates: SENDING, CONTROLLING, HIGH_TRANSMITTING and LOW_TRANSMITTING.
/// When it is in substate SENDING and the bitsToSend >= 0 the new high and low-durations are set after which the new substate HIGH_TRANSMITTING
/// is enabled. When the pin has been high for the specified amount of time (highDuration), the new substate is LOW_TRANSMITTING.
/// When the pin has been LOW for the specified amount of time (lowDuration) the new substate is SENDING again. This continues until bitsToSend < 0.
/// The new substate then becomes CONTROLLING; the controlbits are calculated and sent in the same way as described above. If bitsToSend reaches < 0 in substate
/// controlling, both the state and substate becomes IDLE and a new message can be read again to start the described cycle all over again.
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
         bitsToSend = 15;
         hwlib::cout << hwlib::endl;
      } else if (event == transmitClock && state == states::COMMUNICATING){
         switch(substate){
            case substates::SENDING:
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
/// This function puts the data that has to be transmitted at the first free place in the channel.
/// When the task has time, the data is tranmitted in the main().
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