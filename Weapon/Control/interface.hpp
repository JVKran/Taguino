/// @file

#ifndef __INTERFACE_HPP
#define __INTERFACE_HPP

#include "input.hpp"
#include "KY040.hpp"
#include "rtos.hpp"
#include "display.hpp"
#include "weapon.hpp"

/// \brief
/// Interface Manager
/// \details
/// This class is responsible for managing an interface; the interfaces are managed by the rotary encoder.
class interfaceManager : public encoderListener, public rtos::task<> {
	private:
		display & Display;

		inputHandler & handler;
		KY040 rotaryEncoder;
		weaponManager & weapon;

		rtos::flag encoderPressedFlag;
		int inWhichSetting;
		bool currentlyInSetting = false;

		rtos::flag resetPositionFlag;
		rtos::flag newPositionFlag;
		int currentPosition = 0;

		rtos::pool<int> positionPool;
	public:
		interfaceManager(display & Display, inputHandler & handler, weaponManager & weapon);

		void buttonPressed() override;
		void encoderTurned(const int pos) override;

		void main() override;
};

#endif //__INTERFACE_HPP