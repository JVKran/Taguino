#include "transmitter.hpp"


/// \brief
/// Start of Transmission
/// \details
/// This function makes the transmitterpin high for 2400us and low for 2400us.
/// This condition represents the start of a transmission. This start was chosen since
/// neither a low or high bit is represented this way and thus, it must be something
/// else than interpretable data.
void transmitter::startCondition(){
   transmitter.write(1);
   hwlib::wait_us(2400);
   transmitter.write(0);
   hwlib::wait_us(2400);
}

/// \brief
/// Send Bit
/// \details
/// This function sends one bit whose value is determined by the parameter.
/// The protocol is such that a high bit is represented as a high signal for
/// 1600us and a low signal for 800us. A low bit is represented as a high signal
/// for 800us and a low signal for 1600us. The signal is active low; when the transmitter
/// is transmitting the receiver reads a low signal.
void transmitter::sendBit(const bool bit, const uint16_t duration){
      transmitter.write(1);
      hwlib::wait_us(duration * (1 + bit));
      transmitter.write(0);
      hwlib::wait_us(duration * (1 + !bit));
   }

/// \brief
/// Send Character
/// \details
/// This function transmits the passed character. It does that by calling startCondition() once and
/// sendBit() eight times.
void transmitter::sendChar(const char character){
   startCondition();
   for(int i = 7; i >= 0; i--){
      sendBit((character >> i) & 1UL);
   }
}

/// \brief
/// Send uint16_t
/// \details
/// This function transmits the passed uint16_t. It does that by calling startCondition() once and
/// sendBit() sixteen times. After the data has been send, another transaction is started with the
/// calculated control bits.
void transmitter::sendData(const uint16_t data){
   startCondition();
   controlBits = calculateControlBits(data);
   for(int i = 15; i >= 0; i--){
      sendBit((data >> i) & 1UL);
   }
   for(int i = 7; i >= 0; i--){
      sendBit((controlBits >> i) & 1UL);
   }
}

/// \brief
/// Calculate Control Bits
/// \details
/// This function calculates the control bits based on the passed data. It consists of 8 bits whose
/// value is equal to the xor of bit 0 and bit 7, bit 1 and bit 8, etc.
uint8_t transmitter::calculateControlBits(const uint16_t data){
   controlBits = 0;
   for(unsigned int i = 0; i < 8; i++){
      controlBits |= (((data >> i) & 1UL) ^ ((data >> (i + 8)) & 1UL)) << i;
   }
   //hwlib::cout << "Calculated Controlbits: " << controlBits << hwlib::endl;
   return controlBits;
}