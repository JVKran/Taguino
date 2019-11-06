#ifndef __INPUTG_HPP
#define __INPUTG_HPP

#include "hwlib.hpp"
#include "rtos.hpp"


class buttonListener {
	public:
		virtual void buttonPressed(const char id=0) = 0;
};


class inputHandler;

class button {
	private:
		hwlib::target::pin_in sw = hwlib::target::pin_in( hwlib::target::pins::d4);
		buttonListener * listener;
		inputHandler * handler;

		const char id;
	public:
		button( inputHandler* handler, buttonListener * listener, const char id);

		char getId();
		void update();
};

class inputHandler : public rtos::task<> {
	private:
		int addedButtons = 0;

		std::array<button*, 5> buttons;

		rtos::clock updateClock;
	public:
		inputHandler(unsigned long long int period = 100, const char * name = "Input Handler");

		void addButton(button * b);

		void main() override;
};

#endif //__INPUT_HPP
