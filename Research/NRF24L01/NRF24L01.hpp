#ifndef __NRF24_L01_HPP
#define __NRF24_L01_HPP

class NRF24L01 {
private:
	hwlib::spi_bus & bus; 
	hwlib::pin_out & CE;
	hwlib::pin_out & CSN;

	uint8_t operationAddress;

	uint8_t readRegister(const uint8_t register);
	uint8_t writeRegister(const uint8_t register);

	void selectChip(const bool select = true);

	void enableRX(const bool enable = true);
	void flushRX();

	void enableTX(const bool enable = true);
	void flushTX();

	void sendCommand(const uint8_t command);

	enum class registers{
		R_REGISTER			= 0x00;
		W_REGISTER			= 0x20;
		STATUS				= 0x07;
		CHANNEL_REGISTER	= 0x05;
		RF_SETUP			= 0x06;
		CONFIG_REGISTER		= 0x00;
		SETUP_AW			= 0x03;
		AUTO_ACK_REGISTER	= 0X01;
		EN_LISTENING		= 0x02;
		FIRST_LISTEN_ADDR	= 0x0A;
		FIRST_RX_PLD_SIZE	= 0x11;

		RF_PWR_HIGH			= 2;
		RF_PWR_LOW			= 1;
		RF_DR_HIGH			= 3;
		RF_DR_LOW			= 5;

		SETUP_RETRIES		= 0x04;
		AUTO_RETRY_DELAY	= 4;
		AUTO_RETRY_COUNT 	= 0;
	};

public:
	NRF24L01(hwlib::spi_bus & bus, hwlib::pin_out & CE, hwlib::pin_out & CSN);
	void intializeChip(const uint8_t channelWidth = 5, const uint8_t channelNumber = 1, const uint8_t transmissionPower = 2);

	void setRetries(const uint8_t delay, const uint8_t retryCount);
	void setTransmissionPower(const uint8_t power);
	void setDataRate(const uint8_t dataRate);
	void setAddressWidth(uint8_t addressWidth);

	uint8_t data[32] = {};
	void setPowerMode(const bool turnedOn);

	void setChannel(const uint8_t channel);
	uint8_t getChannel();

	void configureDataPipe(uint8_t pipeNumber, const bool listeningEnabled, const bool autoAck, const uint8_t receptionAddress);
	void bytesAvailable(uint8_t pipeNumber);

	void setTransmissionAddress(const uint8_t address);
	void transmitPayload(const uint8_t address = operationAddress);
	void setPayload()
};

#endif //__NRF24_L01_HPP