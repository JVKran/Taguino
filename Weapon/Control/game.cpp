#include "game.hpp"

runGame::runGame(display & Display, const playerData & player, const int playSeconds, const long long int duration):
	Display(Display),
	player(player),
	irReceiver(irReceiverPin, this, duration),
	secondClock(this, 1'000'000, "Second Clock for Timekeeping"),		//Secondclock fires every second
	receivedDataChannel(this, "Received Data Channel"),
	updateClockTimer(this, "Update Clock Timer")
{
	gameSeconds = playSeconds + 1;										//Startup takes one second
	remainingSeconds = playSeconds;
	Display.showTime(remainingSeconds);
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
		} else {
			Display.showTime(remainingSeconds);							//Update time on display every gameTime / 100; 
			updateClockTimer.set((gameSeconds / 100 )* 1'000'000);		//so time on display is updated 100 times during the entire game.
		}
	}
}