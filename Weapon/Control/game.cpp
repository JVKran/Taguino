#include "game.hpp"

runGame::runGame(const playerData & player):
	player(player)
{}

playerData runGame::getPlayerData(){
	return player;
}