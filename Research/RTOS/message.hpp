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
		rtos::channel< uint_fast64_t, 1024 > pauses;

		enum class states {idle, message};
		states state;

		int n;		//Index of received bit
		int m;		//Received message
	public:
		messageDecoder(messageListener & listener);

		void pauseDetected(const uint_fast64_t pause) override;
		void main() override;
};

//<<<<<<<<<<<<<<<<<<<------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>

class messageLogger : public rtos::task<>, public messageListener {
	private:
		rtos::channel<int, 1024> messages;
		rtos::timer clearDisplayTimer;

		enum class states {idle, showmessage};
		states state = states::idle;
	public:
		messageLogger(const char * name);

		void messageReceived(const int m) override {
			messages.write(m);
		}
		void main() override;
};

#endif //__MESSAGE_HPP