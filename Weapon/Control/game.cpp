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
	Display.showHealthBar();
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
			receivedData = receivedDataChannel.read();
			hwlib::cout << "Data Received: " << int(receivedData) << hwlib::endl;
			hwlib::cout << "Distance: " << (receivedData & 0x3F) * 10 << "cm. "<< hwlib::endl;
			hwlib::cout << "Playernumber: " << (receivedData >> 10) << hwlib::endl;
			hwlib::cout << "Weapon: " << ((receivedData & 0x1C0) >> 6);
		} else if (event == secondClock) {
			remainingSeconds--;
			Display.drawHealth(remainingSeconds / 10);
		} else {
			Display.showTime(remainingSeconds, gameSeconds);
			updateClockTimer.set((gameSeconds / 100 )* 1'000'000);
		}
	}
}