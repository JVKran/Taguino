#ifndef __MESSAGE_HPP
#define __MESSAGE_HPP

#include "pause.hpp"

class messageListener {
	public:
		virtual void messageReceived(const int m) = 0;	
};

//<<<<<<<<<<<<<<<<<<<------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>

class messageDecoder : public rtos::task<>, public pauseListener {
	private:
		messageListener & listener;
		rtos::channel< int, 1024 > pauses;

		enum class states {idle, message};
		states state;

		int n;		//Index of received bit
		int m;		//Received message
	public:
		messageDecoder(messageListener & listener);

		void pauseDetected(const int n) override;
		void main() override;
};

//<<<<<<<<<<<<<<<<<<<------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>

class messageLogger : public rtos::task<>, public messageListener {
	private:
		hwlib::i2c_bus_bit_banged_scl_sda & bus;
		hwlib::font_default_16x16 messageFont = hwlib::font_default_16x16();
		hwlib::window_part messageWindow = hwlib::window_part(oled, hwlib::xy(0,0),hwlib::xy(100,20));
		hwlib::terminal_from messageTerminal = hwlib::terminal_from(messageWindow, messageFont);
		hwlib::glcd_oled oled;

		rtos::channel<int, 1024> messages;
		rtos::timer clearDisplayTimer;

		enum class states {idle, showmessage};
		states state = states::idle;

	public:
		messageLogger(hwlib::i2c_bus_bit_banged_scl_sda & bus, const char * name = "");

		void messageReceived(const int m) override {
			messages.write(m);
		}
		void main() override;
};

#endif //__MESSAGE_HPP