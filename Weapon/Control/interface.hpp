#ifndef __INTERFACE_HPP
#define __INTERFACE_HPP

#include "input.hpp"
#include "KY040.hpp"
#include "rtos.hpp"
#include "display.hpp"

class interfaceManager : public encoderListener, public rtos::task<> {
	private:
		display & Display;

		inputHandler handler;
		KY040 rotaryEncoder;

		rtos::flag encoderPressedFlag;
		int inWhichSetting;
		bool currentlyInSetting = false;

		rtos::flag resetPositionFlag;
		rtos::flag newPositionFlag;
		int currentPosition = 0;

		rtos::pool<int> positionPool;
	public:
		interfaceManager(display & Display, inputHandler & handler);

		void buttonPressed() override;
		void encoderTurned(const int pos) override;

		void main() override;
};

#endif //__INTERFACE_HPP