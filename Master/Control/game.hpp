#ifndef __GAME_HPP
#define __GAME_HPP

#include "NRF24.hpp"
#include "entities.hpp"
#include "applicationLogic.hpp"

class game : public radioListener {
private:
	NRF24 & radio;
	scoreBoard board;

	int amountOfDataToTransmit = 5;
	uint8_t dataToTransmit[5];

	uint8_t receiveAddress[5] = {0, 0, 0, 0, 0};
	uint8_t transmitAddress[5] = {0, 0, 0, 0, 0};

	uint8_t assignedWeapons = 5;

public:
	game(NRF24 & radio);
	virtual void dataReceived(const uint8_t data[10], const int len) override;
};


#endif //__GAME_HPP