#ifndef __TRANSCEIVER_HPP
#define __TRANSCEIVER_HPP

class transmit{
	protected:
		hwlib::pin_out & transmitPin;
	public:
		transmit(hwlib::pin_out & transmitPin);
		void send(const uint16_t & content);
};

class receive{
	protected:
		hwlib::pin_in & receivePin;
	public:
		receive(hwlib::pin_in & receivePin);
		bool available();
		uint16_t read();
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