#include "game.hpp"

runGame::runGame(const playerData & player):
	player(player),
	secondClock(this, 1'000'000, "Second Clock for Timekeeping"),
	receivedDataChannel(this, "Received Data Channel")
{}

playerData runGame::getPlayerData(){
	return player;
}

void runGame::dataReceived(const uint16_t data){
	receivedDataChannel.write(data);
}

void runGame::main(){
	for(;;){
		auto event = wait(receivedDataChannel+secondClock);
		if(event == receivedDataChannel){
			hwlib::cout << "Received " << receivedDataChannel.read() << "!!!";
		} else {
			hwlib::cout << "One second passed..." << hwlib::endl;
		}
	}
}