#include "NRF24L01.hpp"

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
void NRF24L01::write_register(const uint8_t register, const uint8_t content){
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

/// \brief
/// Enable RX
/// \details
/// The CE-pin has to be made low for RX to be enabled.
void NRF24L01::enableTX(const bool enable){
	CE.write(!enable);
	CE.flush();
}