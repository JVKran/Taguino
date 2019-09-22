/// @file

#include "transceiver.hpp"

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
void transmitter::sendBit(const bool bit){
      transmitter.write(1);
      hwlib::wait_us(800 * (1 + bit));
      transmitter.write(0);
      hwlib::wait_us(800 * (1 + !bit));
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
/// sendBit() sixteen times.
void transmitter::sendData(const uint16_t data){
   startCondition();
   for(int i = 15; i >= 0; i--){
      sendBit((data >> i) & 1UL);
   }
}

/// \brief
/// Constructor
/// \details
/// This constructor has one mandatory parameter; the pin to which the receiver is attached.
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
/// It first waits for the signal to become low (which is a high signal from the receiver);
/// Thus the signal is active low.
/// It does that since only the duration of the high signal is of interest; that duration determines
/// if the transmitter sent a 1 or 0.
/// If a high signal has been received for more than 800us a 1 has been send; 0 otherwise.
bool receiver::readBit(){
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
   return (highDuration > 800) ? true : false;
}

/// \brief
/// Read Char
/// \details
/// This function returns the character that has been received. This function calls readBit() eight
/// times since a char consists of eight bits.
char receiver::readChar(){
   receivedChar = 0;
   for(int i = 7; i >= 0; i--){
      receivedChar |= (readBit() << i);
   }
   return receivedChar;
}

/// \brief
/// Read Data
/// \details
/// This function returns the uint16_t that has been received. This function calls readBit() sixteen
/// times since a uint16_t consists of sixteen bits.
uint16_t receiver::readData(){
   receivedData = 0;
   for(int i = 15; i >= 0; i--){
      receivedData |= (readBit() << i);
   }
   return receivedData;
}

/// \brief
/// Read Raw Data
/// \details
/// This function was and is being used for debugging purposes. It is only able to read 8 bits at a time
/// but that's all that's needed to debug and finetune communication. This function prints a decimal representation
/// of the received character and of course the character itself.
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
