#ifndef __INTERFACE_HPP
#define __INTERFACE_HPP

#include "input.hpp"
#include "KY040.hpp"

class interfaceManager : public encoderListener {
	private:
		inputHandler handler;
		KY040 rotaryEncoder;
	public:
		interfaceManager(inputHandler & handler);

		void buttonPressed() override;
		void encoderTurned(const int pos) override;
};

#endif //__INTERFACE_HPP