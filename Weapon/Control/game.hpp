#ifndef __GAME_HPP
#define __GAME_HPP

#include "entities.hpp"
#include "RGBLed.hpp"

class runGame {
	private:
		playerData player;

    	RGBLed Led = RGBLed();
	public:
		runGame(const playerData & player);
		playerData getPlayerData();
};


#endif //__GAME_HPP