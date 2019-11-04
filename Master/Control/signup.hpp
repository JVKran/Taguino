#ifndef __SIGNUP_HPP
#define __SIGNUP_HPP

#include "NRF24.hpp"

class signUp : public radioListener {
private:
	NRF24 radio;

	std::array<int, 31> onlineWeapons;			//Array with weaponNumbers that have been turned on.
	int assignedWeapons;
public:
	signUp(NRF24 & radio);
	virtual void dataReceived(const uint8_t data[], const int len) override;
};

#endif //__SIGNUP_HPP