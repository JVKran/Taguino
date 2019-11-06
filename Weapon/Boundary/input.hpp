#ifndef __INPUT_HPP
#define __INPUT_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "button.hpp"
#include "KY040.hpp"

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
		buttonRegister * buttonsRegister;

		const int buttonNotToBeSet;
		const char id;
	public:
		button(const int pinNumber, inputHandler* handler, buttonListener * listener, const char id, const int buttonNotToBeSet = 0);

		char getId();
		void update();
};

class inputHandler : public rtos::task<> {
	private:
		KY040* encoder;
		int addedButtons = 0;

		std::array<button*, 10> buttons;
		buttonRegister buttonsRegister;

		rtos::clock updateClock;
		enum class states {IDLE, UPDATING};
		states state = states::IDLE;
	public:
		inputHandler(unsigned long long int period = 100'000, const char * name = "Input Handler");

		void addButton(button * b);
		void addEncoder(KY040 * e);

		buttonRegister * getRegister();

		void main() override;
};

#endif //__INPUT_HPP
