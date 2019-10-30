#include "game.hpp"

runGame::runGame(display & Display, const playerData & player, const int playSeconds):
	Display(Display),
	player(player),
	secondClock(this, 1'000'000, "Second Clock for Timekeeping"),
	receivedDataChannel(this, "Received Data Channel"),
	updateClockTimer(this, "Update Clock Timer")
{
	gameSeconds = playSeconds;
	remainingSeconds = playSeconds;
	Display.showTime(remainingSeconds, gameSeconds);
}

playerData runGame::getPlayerData(){
	return player;
}

void runGame::dataReceived(const uint16_t data){
	receivedDataChannel.write(data);
}

void runGame::main(){
	updateClockTimer.set((gameSeconds / 100 )* 1'000'000);
	for(;;){
		auto event = wait(receivedDataChannel+secondClock+updateClockTimer);
		if(event == receivedDataChannel){
			hwlib::cout << "Received " << receivedDataChannel.read() << "!!!";
		} else if (event == secondClock) {
			remainingSeconds--;
		} else {
			Display.showTime(remainingSeconds, gameSeconds);
			updateClockTimer.set((gameSeconds / 100 )* 1'000'000);
		}
	}
}