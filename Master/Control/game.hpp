#ifndef __GAME_HPP
#define __GAME_HPP

#include "NRF24.hpp"
#include "entities.hpp"

class game : public radioListener {
private:
	NRF24 & radio;
	scoreBoard board = scoreBoard();

	uint8_t dataToTransmit[5];
	uint8_t receiveAddress = {0, 0, 0, 0, 0};
	uint8_t transmitAddress = {0, 0, 0, 0, 0};
public:
	game(NRF24 & radio);
	virtual void dataReceived(const uint8_t data[], const int len) override;
}


#endif //__GAME_HPP