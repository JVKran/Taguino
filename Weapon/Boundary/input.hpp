#ifndef __INPUT_HPP
#define __INPUT_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class buttonListener {
	public:
		virtual void buttonPressed(const char id) = 0;
};

class button {
	private:
		hwlib::target::pin_in buttonPin;
		buttonListener * listener;

		const char id;
	public:
		button(buttonListener * listener, const char id, hwlib::target::pin_in buttonPin);

		char getId();
		void update();
};

class inputHandler : public rtos::task<> {
	private:
		std::array<button*, 5> buttons;
		int addedButtons = 0;
		rtos::clock updateClock;
	public:
		inputHandler(unsigned long long int period = 100, const char * name = "Input Handler");

		void addButton(button * b);
		void main() override;
};

#endif //__INPUT_HPP
