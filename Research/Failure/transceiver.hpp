#ifndef __TRANSCEIVER_HPP
#define __TRANSCEIVER_HPP

class transmit{
	private:
		hwlib::pin_out & transmitPin;
		void sendBit(const bool bit);
	public:
		transmit(hwlib::pin_out & transmitPin);
		void send(const uint16_t content);
};

class receive{
	protected:
		hwlib::pin_in & receivePin;
	public:
		receive(hwlib::pin_in & receivePin);
};

//void send both has to transmit and receive for verification of data-integrity
class transceiver{
	private:
		transmit transmitter;
		receive receiver;
	public:
		transceiver(transmit & transmitter, receive & receiver);
};


#endif //__TRANSCEIVER_HPP