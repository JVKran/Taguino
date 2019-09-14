#include "NRF24L01.hpp"


NRF24L01::NRF24L01(hwlib::spi_bus & bus, hwlib::pin_out & CE, hwlib::pin_out & CSN):
   bus(bus),
   CE(CE),
   CSN(CSN)
{
   setPowerMode(false);
}

void NRF24L01::initializeChip(const uint8_t channelWidth, const uint8_t channelNumber, const uint8_t transmissionPower){
   writeRegister(STATUS, 0x0C);
   setRetries(5, 15);
   setAddressWidth(channelWidth);
   setTransmissionPower(transmissionPower);
   setDataRate(1);

   setChannel(channelNumber);

   flushRX();
   flushTX();

   setPowerMode(true);

}

void NRF24L01::sendCommand(const uint8_t command){
   selectChip();
   bus.transaction(hwlib::pin_out_dummy).write(command);
   selectChip(false);
}

/// \brief
/// Read Single Register
/// \details
/// First the chip has to be selected. After that, we use the Read Register command (first 3 bits) and
/// OR that value with the desired register (last 5 bits). The value in that register is returned.
uint8_t NRF24L01::readRegister(const uint8_t register){
   selectChip();
   bus.transaction(hwlib::pin_out_dummy).write(R_REGISTER|(0x1F & register));
   uint8_t result = bus.transaction(hwlib::pin_out_dummy).read_byte();
   selectChip(false);
   return result;
}

/// \brief
/// Write Single Register
/// \details
/// First the chip has to be selected. After that, we use the Write Register command (first 3 bits) and
/// OR that value with the desired register (last 5 bits). After that, we send the value we want to put
/// in that register. Finally, the chip is deselected again.
void NRF24L01::writeRegister(const uint8_t register, const uint8_t content){
   selectChip();
   bus.transaction(hwlib::pin_out_dummy).write((W_REGISTER|(0x1F & register)));
   bus.transaction(hwlib::pin_out_dummy).write(value);
   selectChip(false);
}

/// \brief
/// Chip Select
/// \details
/// This pin has to be made high to enable SPI communication.
void NRF24L01::selectChip(const bool select){
	CSN.write(!enable);
	CSN.flush();
}

/// \brief
/// Enable RX
/// \details
/// The CE-pin has to be made high for RX to be enabled.
void NRF24L01::enableRX(const bool enable){
	CE.write(enable);
	CE.flush();
}

void NRF24L01::flushRX(){
   sendCommand(0xE2);
}

/// \brief
/// Enable RX
/// \details
/// The CE-pin has to be made low for RX to be enabled.
void NRF24L01::enableTX(const bool enable){
	CE.write(!enable);
	CE.flush();
}

void NRF24L01::flushTX(){
   sendCommand(0xE1);
}

/// \brief
/// Set Power-Mode
/// \details
/// When true is passed, a one will be written at index 1 in the config register.
/// The chip will then be powered on. If false is passed, the device will turn off.
void NRF24L01::setPowerMode(const bool turnedOn){
   if(turnedOn){
      writeRegister(CONFIG_REGISTER, readRegister(CONFIG_REGISTER)|turnedOn << 1);
   } else {
      writeRegister(CONFIG_REGISTER, readRegister(CONFIG_REGISTER)& ~(turnedOn << 1));
   }
}

/// \brief
/// Set channel
/// \details
/// Sets the frequency channel the chip operates on.
void NRF24L01::setChannel(const uint8_t channel){
   if(channel > 125){
      writeRegister(CHANNEL_REGISTER, 125);
   } else {
      writeRegister(CHANNEL_REGISTER, channel);
   }
}

/// \brief
/// Get channel
/// \details
/// Returns the frequency channel the chip operates on.
uint8_t NRF24L01::getChannel(){
   return readRegister(CHANNEL_REGISTER);
}

void NRF24L01::setAddressWidth(uint8_t addressWidth){
   addressWidth -= 2;
   if(width >= 1 && width <= 5){
      writeRegister(SETUP_AW, addressWidth);
   } else {
      setAddressWidth(5);
   }
}

/// \brief
/// Configure One Data Pipe
/// \details
/// This function takes care of everything needed to get started with data pipes.
void NRF24L01::configureDataPipe(uint8_t pipeNumber, const bool listeningEnabled, const bool autoAck, const uint8_t receptionAddress){
   if(pipeNumber > 5){
      pipeNumber = 5;
   }
   if(autoAck){
      writeRegister(AUTO_ACK_REGISTER, readRegister(AUTO_ACK_REGISTER) | (1UL << pipeNumber));
   } else {
      writeRegister(AUTO_ACK_REGISTER, readRegister(AUTO_ACK_REGISTER) & ~(1UL << pipeNumber));
   }
   if(listeningEnabled){
      writeRegister(EN_LISTENING, readRegister(EN_LISTENING) | (1UL << pipeNumber));
   } else {
      writeRegister(EN_LISTENING, readRegister(EN_LISTENING) & ~(1UL << pipeNumber));
   }
   writeRegister(FIRST_LISTEN_ADDR + pipeNumber, receptionAddress);
}

/// \brief
/// Get Amount of Bytes in Buffer
/// \details
/// This function returns the amount of bytes in the RX payload of the passed data pipe.
uint8_t NRF24L01::bytesAvailable(uint8_t pipeNumber){
   if(pipeNumber > 5){
      pipeNumber = 5;
   }
   return readRegister(FIRST_RX_PLD_SIZE + pipeNumber);
}

/// \brief
/// Set Data-Rate
/// \details
/// This function sets the data rate at wich data is sent. Possible parametres are 1 and 2
/// for respectively 1 and 2 Mbps. For other values a speed of 250Kbps is set.
void NRF24L01::setDataRate(const uint8_t dataRate){
      if(dataRate == 1){
         writeRegister(RF_SETUP, readRegister(RF_SETUP) & ~((1 << RF_DR_LOW)  | (1 << RF_DR_HIGH)));
      } else if (dataRate == 2){
         writeRegister(RF_SETUP, (readRegister(RF_SETUP) & ~(1 << RF_DR_LOW)) | (1 << RF_DR_HIGH));
      } else { 
         writeRegister(RF_SETUP, (readRegister(RF_SETUP) | (1 << RF_DR_LOW)) & ~(1 << RF_DR_HIGH));
      }
}

/// \brief
/// Set Transmission Power
/// \details
/// This function sets the maximum transmission power the device is allowed to transmit data with.
void NRF24L01::setTransmissionPower(const uint8_t power){
   if(power == 1){
      writeRegister(RF_SETUP, (readRegister(RF_SETUP) | 1 << RF_PWR_LOW) & ~(1 <<  RF_PWR_HIGH));
   } else if (power == 2){
      writeRegister(RF_SETUP, (readRegister(RF_SETUP) |  1 <<  RF_PWR_HIGH) & ~(1 << RF_PWR_LOW));
   } else if (power == 3){
      writeRegister(RF_SETUP, readRegister(RF_SETUP) | ( 1 <<  RF_PWR_HIGH | 1 << RF_PWR_LOW));
   } else {
      writeRegister(RF_SETUP, readRegister(RF_SETUP) & ~( 1 <<  RF_PWR_HIGH | 1 << RF_PWR_LOW));
   }
}

void NRF24L01::setRetries(const uint8_t delay, const uint8_t retryCount){
   writeRegister(SETUP_RETRIES, (delay & 0xF) << AUTO_RETRY_DELAY | (count & 0xF) << AUTO_RETRY_COUNT);
}