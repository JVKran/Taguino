#include "input.hpp"

class weaponManager : public buttonListener {
	private:
		button triggerButton;
		button autoButton;
		inputHandler handler;
	public:
		weaponManager(inputHandler & handler);

		virtual void buttonPressed(const char id) override;
};