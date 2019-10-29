#ifndef __INTERFACE_HPP
#define __INTERFACE_HPP

#include "input.hpp"
#include "KY040.hpp"
#include "rtos.hpp"

class interfaceManager : public encoderListener, public rtos::task<> {
	private:
		inputHandler handler;
		KY040 rotaryEncoder;

		rtos::flag encoderPressedFlag;
		rtos::flag resetPositionFlag;
		rtos::flag newPositionFlag;

		rtos::pool<int> positionPool;
	public:
		interfaceManager(inputHandler & handler);

		void buttonPressed() override;
		void encoderTurned(const int pos) override;

		void main() override;
};

#endif //__INTERFACE_HPP