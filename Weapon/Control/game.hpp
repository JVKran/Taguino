#ifndef __GAME_HPP
#define __GAME_HPP

#include "entities.hpp"

class runGame {
	private:
		playerData player;
	public:
		runGame(const playerData & player);
		playerData getPlayerData();
};


#endif //__GAME_HPP