#ifndef __INPUT_HPP
#define __INPUT_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "KY040.hpp"
#include "button.hpp"

class KY040;

class buttonListener {
	public:
		virtual void buttonPressed(const char id) = 0;
};

class encoderListener {
	public:
		virtual void buttonPressed() = 0;
		virtual void encoderTurned(const int pos) = 0;
};

class inputHandler;

class button {
	private:
		const int pinNumber;
		buttonListener * listener;
		inputHandler * handler;
		Buttoninterrupter * buttonRegister;

		const char id;
	public:
		button(const int pinNumber, inputHandler* handler, buttonListener * listener, const char id);

		char getId();
		void update();
};

class inputHandler : public rtos::task<> {
	private:
		KY040* encoder;
		int addedButtons = 0;

		std::array<button*, 5> buttons;
		Buttoninterrupter buttonInterrupter;

		rtos::clock updateClock;
	public:
		inputHandler(unsigned long long int period = 100'000, const char * name = "Input Handler");

		void addButton(button * b);
		void addEncoder(KY040 * e);

		Buttoninterrupter * getRegister();

		void main() override;
};

#endif //__INPUT_HPP
