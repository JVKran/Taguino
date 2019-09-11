#ifndef __NRF24_L01_HPP
#define __NRF24_L01_HPP

class NRF24L01 {
private:
	hwlib::spi_bus & bus; 
	hwlib::pin_out & CE;
	hwlib::pin_out & CSN;

	uint8_t readRegister(const uint8_t register);
	uint8_t writeRegister(const uint8_t register);

	void selectChip(const bool select = true);
	void enableRX(const bool enable = true);
	void enableTX(const bool enable = true);

	enum class registers{
		R_REGISTER			= 0x00;
		W_REGISTER			= 0x20;
	};

public:
};

#endif //__NRF24_L01_HPP