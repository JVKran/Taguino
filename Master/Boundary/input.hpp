/// @file

#ifndef __INPUT_HPP
#define __INPUT_HPP


#include "hwlib.hpp"
#include "rtos.hpp"
#include "button.hpp"
#include "KY040.hpp"
#include "keypad.hpp"
//#include "signup.hpp"

class KY040;

/// \brief
/// Button Listener
/// \details
/// This class defines a function that gets caled when a button is pressed.
class buttonListener {
	public:
		virtual void buttonPressed(const char id) = 0;
};

/// \brief
/// Encoder Listener
/// \details
/// This function gets called when the encoder gets pressed or turned.
class encoderListener {
	public:
		virtual void buttonPressed() = 0;
		virtual void encoderTurned(const int pos) = 0;
};

class inputHandler;

/// \brief
/// Button 
/// \details
/// The button gets updated on update() call. It then checks the register that gets updated by the inputHandler.
/// When it is pressed it calls the listener.buttonPressed() function.
class button {
	private:
		const int pinNumber;
		buttonListener * listener;
		inputHandler * handler;
		Buttoninterrupter * buttonRegister;

		const int buttonNotToBeSet;
		const char id;
	public:
		button(const int pinNumber, inputHandler* handler, buttonListener * listener, const char id, const int buttonNotToBeSet = 0);

		char getId();
		void update();
};

/// \brief
/// Input Handler
/// \details
/// The class is responsible for updating all input boundary objects.
class inputHandler : public rtos::task<> {
	private:
		KY040* encoder;
		int addedButtons = 0;

		std::array<button*, 10> buttons;
		Buttoninterrupter buttonInterrupter;

		rtos::clock updateClock;
		T9Keys* toetsenbord;
	public:
		inputHandler(unsigned long long int period = 100'000, const char * name = "Input Handler");

		void addButton(button * b);
		void addEncoder(KY040 * e);
		void addkeypad(T9Keys *t);

		Buttoninterrupter * getRegister();

		void main() override;
};

#endif //__INPUT_HPP
