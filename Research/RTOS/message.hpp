#ifndef __MESSAGE_HPP
#define __MESSAGE_HPP

#include "pause.hpp"

class messageDecoder : public rtos::task<>, public pauseListener {
	private:
		messageListener & listener;
		enum class states {idle, message};
		states state;
		rtos::channel< uint_fast64_t, 1024 > pauses;
	public:
		messageDecoder(const pauseListener & listener);

		void pauseDetected(const uint_fast64_t pause) override;

		void main() override;
};


class messageListener {
	public:
		messageReceived(const infraredMessage & message) = 0;
};


class messageLogger : pulic rtos::task<>, public messageListener {
	public:
		rtos::channel< int, 1024 > messages;
};

#endif //__MESSAGE_HPP