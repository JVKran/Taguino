#ifndef __TRANSCEIVER_HPP
#define __TRANSCEIVER_HPP

class transmitter{
	protected:
		hwlib::pin_out & transmitPin;
	public:
		transmitter(hwlib::pin_out & transmitPin);
		void transmit(const char value);
};


#endif //__TRANSCEIVER_HPP