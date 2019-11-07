/// @file

#include "receiver.hpp"


/// \brief
/// Constructor
/// \details
/// This constructor has two mandatory parameters; the listener to notify when a new highduration has been
/// measured and the period to check for a new signal. Then there's also a clock object created which fires every
/// period and a task.
infraredReceiver::infraredReceiver(highSignalListener & listener, const long long int period):
   task(0, "Signal Detecting Task"),
   listener(listener),
   sampleClock(this, period, "Sample Clock"),
   period(period)
{}

/// \brief
/// Infrared Receiving Task
/// \details
/// This task is responsible for one single thing; detecting high Signals and their durations.
/// When the duration of a high signal has been measured (and thus the pin becomes low again)
/// the highSignalDetected() is called on the listnening object.
void infraredReceiver::main(){
   for(;;){
      wait(sampleClock);
      switch(state){
         case states::SIGNAL:
            if(!irReceiver.read()){       //If transmitter is transmitting (high)
               highDuration += period;
            } else {                      //If transmitter is not transmitting
               listener.highSignalDetected(highDuration);
               state = states::IDLE;
            }
            break;
         case states::IDLE:
            if(!irReceiver.read()){       //If transmitter is transmitting a new signal is beeing broadcasted
               state = states::SIGNAL;
               highDuration = 0;
            }
            break;
      }
   }
}

/// \brief
/// Constructor
/// \details
/// This constructor has one mandatory parameter; the messageListener to notify when a signal has been detected.
/// There also is a channel created which contains the high durations; based on these the signal can be decoded.
infraredDecoder::infraredDecoder(messageListener & listener):
   task(2, "Infrared Decoder"),
   listener(listener),
   highDurations(this, "High Durations Channel")
{}

/// \brief
/// High Signal Detected
/// \details
/// This function places the parameter in the highDurationsChannel.
void infraredDecoder::highSignalDetected(const int highDuration){
   highDurations.write(highDuration);
}

/// \brief
/// Calculate Control Bits
/// \details
/// This function calculates the control bits based on the passed data. It consists of 8 bits whose
/// value is equal to the xor of bit 0 and bit 7, bit 1 and bit 8, etc.
uint8_t infraredDecoder::calculateControlBits(const uint16_t data){
   controlBits = 0;
   for(unsigned int i = 0; i < 8; i++){
      controlBits |= (((data >> i) & 1UL) ^ ((data >> (i + 8)) & 1UL)) << i;
   }
   return controlBits;
}

/// \brief
/// Infrared Decoding Task
/// \details
/// This function uses the highDurations in the channel to determine what data has been received.
/// A complete infrared message can only be started by a startConditions; 2400us high signal followed by a low signal for 2400us.
/// When such a highDuration is received the state changes from IDLE to MESSAGE and every used attribute is set to 0.
/// For the next 16 bits a logic 1 is received when the duration is higher than 1200us and a logic 0 if it is lower than 1200us.
/// The real duration for high vs low is 1600 vs 800 but 1200 is a nice switchpoint.
/// If 16 bits have been received it's time to start checking the controlbits; hence the new state is CONTROL. The process described
/// above is repeated 8 times for the controlbits after which the value of the controlbits is calculated. If the received controlbits
/// are equal to the calculated ones, the messageListener is notified of a new message. Else, the value is thrown away.
void infraredDecoder::main(){
   for(;;){
      wait(highDurations);
      highDuration = highDurations.read();
      switch(state){
         case states::IDLE:
            if(highDuration > 2000 && highDuration < 2800){
               state = states::MESSAGE;
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
               }
            } else {
               state = states::IDLE;
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
                  }
               }
            } else {
               state = states::IDLE;
            }
            break;
      }
   }
}