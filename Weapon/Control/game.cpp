#include "game.hpp"

runGame::runGame(display & Display, const playerData & player, hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBus, const long long int duration, rtos::task<> & handler):
	Display(Display),
	player(player),
	exchanger(exchangeGameData(this, spiBus, duration)),
	secondClock(this, 1'000'000, "Second Clock for Timekeeping"),		//Secondclock fires every second
	receivedDataChannel(this, "Received Data Channel"),
	updateClockTimer(this, "Update Clock Timer"),
	handler(handler)
{
	handler.suspend();
}

playerData runGame::getPlayerData(){
	return player;
}

void runGame::messageReceived(const uint16_t data){
	receivedDataChannel.write(data);
}

void runGame::gameStartSignalReceived(const uint8_t timeToPlay){
	handler.resume();
	gameSeconds = timeToPlay * 10;
	remainingSeconds = timeToPlay * 10;
	Display.showTime(timeToPlay * 10, timeToPlay * 10);
	updateClockTimer.set((gameSeconds / 100 )* 1'000'000);
	Display.showHealthBar();
}

void runGame::main(){
	for(;;){
		auto event = wait(receivedDataChannel+secondClock+updateClockTimer);
		if(event == receivedDataChannel){
			receivedData = receivedDataChannel.read();
			hwlib::cout << 'I' << hwlib::endl;
			distance = (receivedData & 0x3F) * 10;
			playerNumber = (receivedData >> 10);
			weaponId = ((receivedData & 0x1C0) >> 6);
			dealtDamage = weaponStats.getDamage((receivedData & 0x1C0) >> 6, (receivedData & 0x3F));
			if(playerNumber != player.getPlayerNumber()){				//If player didn't shoot himself
				exchanger.updateScore(playerNumber, dealtDamage);
				player.setHealth(player.getHealth() - dealtDamage);
				//Display.showHealth(player.getHealth()); Crashes Program...
				hwlib::cout << "New Health: " << player.getHealth() << hwlib::endl;
			}
		} else if (event == secondClock) {
			remainingSeconds--;
		} else {
			Display.showTime(remainingSeconds);							//Update time on display every gameTime / 100; 
			updateClockTimer.set((gameSeconds / 100 )* 1'000'000);		//so time on display is updated 100 times during the entire game.
		}
	}
}

exchangeGameData::exchangeGameData(runGame * game, hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBus, const long long int duration):
	game(game),
	radio(NRF24(spiBus, ce, csn, duration, game->getPlayerData().getPlayerNumber()))
{
	radio.addListener(this);
}

void exchangeGameData::updateScore(const uint8_t playerNumber, const uint8_t dealtDamage){
	radio.write_pipe( 0x00 );				//Master address = 0x00
   	radio.powerDown_rx();

   	dataToTransmit[0] = playerNumber;
   	dataToTransmit[1] = dealtDamage;

	radio.write( dataToTransmit, amountOfDataToTransmit );
	address[4] = game->getPlayerData().getPlayerNumber();
   	radio.read_pipe(address);
   	radio.powerUp_rx();
}

void exchangeGameData::dataReceived(const uint8_t data[], const int len){
	for(int i = 0; i < len; i++){
		hwlib::cout << data[i] << " ";
	}
	hwlib::cout << hwlib::endl;
	switch(data[0]){
		case 1:
			hwlib::cout << "Game started" << hwlib::endl;
			game->gameStartSignalReceived(data[1]);
			break;
		case 2:
			hwlib::cout << "Playernumber " << data[1] << " has a score of " << data[2] << " hence his position is " << data[3] << hwlib::endl;
			break;
		case 3:
			hwlib::cout << "InfiniteBullets Activated" << hwlib::endl;
			break;
		case 4:
			hwlib::cout << "InstaDeath Activated" << hwlib::endl;
			break;
		case 5:
			hwlib::cout << "Time to Play: " << data[1] << " out of " << data[2] << " seconds." << hwlib::endl;
			break;
		case 6:
			hwlib::cout << "PlayerNumber " << data[1] << " has name " << data[2] << data[3] << data[4] << hwlib::endl;
			break;
	}
}