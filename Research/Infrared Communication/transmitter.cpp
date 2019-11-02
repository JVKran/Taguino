#include "transmitter.hpp"


infraredTransmitter::infraredTransmitter():
   task("Infrared Transmitting Task"),
   transmitClock(this, 100, "Transmitting Clock"),
   highDurations(this, "Channel with durations of high signals")
{}

/// \brief
/// Send Bit
/// \details
/// This function sends one bit whose value is determined by the parameter.
/// The protocol is such that a high bit is represented as a high signal for
/// 1600us and a low signal for 800us. A low bit is represented as a high signal
/// for 800us and a low signal for 1600us. The signal is active low; when the transmitter
/// is transmitting the receiver reads a low signal.
void infraredTransmitter::sendBit(const bool bit){
   highDurations.write(800 * (1 + bit));
}

/// \brief
/// Start of Transmission
/// \details
/// This function makes the transmitterpin high for 2400us and low for 2400us.
/// This condition represents the start of a transmission. This start was chosen since
/// neither a low or high bit is represented this way and thus, it must be something
/// else than interpretable data.
void infraredTransmitter::sendStartCondition(){
   highDurations.write(2400);
}

void infraredTransmitter::main(){
   for(;;){
      auto event = wait(transmitClock+highDurations);
      if(event == highDurations && state == states::IDLE){
         highDuration = highDurations.read();
         //hwlib::cout << highDuration << hwlib::endl;
         state = states::TRANSMITTING;
         transmitter.write(1);
         transmittedDuration = hwlib::now_us();
      } else if (event == transmitClock) {
         switch(state){
            case states::NOT_TRANSMITTING:
               if(highDuration == 1600){
                  if(hwlib::now_us() - lowDuration > 800){
                     state = states::IDLE;
                  }
               } else if (highDuration == 800){
                  if(hwlib::now_us() - lowDuration > 1600){
                     state = states::IDLE;
                  }
               } else {
                  if(hwlib::now_us() - lowDuration > 2400){
                     state = states::IDLE;
                  }
               }
               break;
            case states::TRANSMITTING:
               if(hwlib::now_us() - transmittedDuration > highDuration){
                  lowDuration = hwlib::now_us();
                  transmitter.write(0);
                  state = states::NOT_TRANSMITTING;
               }
               break;
            default:
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
void infraredEncoder::sendData(const uint16_t data){
   transmitter.sendStartCondition();
   controlBits = calculateControlBits(data);
   for(int i = 15; i >= 0; i--){
      transmitter.sendBit((data >> i) & 1UL);
   }
   for(int i = 7; i >= 0; i--){
      transmitter.sendBit((controlBits >> i) & 1UL);
   }
}

/// \brief
/// Calculate Control Bits
/// \details
/// This function calculates the control bits based on the passed data. It consists of 8 bits whose
/// value is equal to the xor of bit 0 and bit 7, bit 1 and bit 8, etc.
uint8_t infraredEncoder::calculateControlBits(const uint16_t data){
   controlBits = 0;
   for(unsigned int i = 0; i < 8; i++){
      controlBits |= (((data >> i) & 1UL) ^ ((data >> (i + 8)) & 1UL)) << i;
   }
   //hwlib::cout << "Calculated Controlbits: " << controlBits << hwlib::endl;
   return controlBits;
}