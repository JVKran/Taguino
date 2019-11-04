/// @file

#include "game.hpp"


/// \brief
/// Constructor
/// \details
/// This constructor has a couple of mandatory parameters; A display which is needed to show the time, health and powerups, an SPI-Bus needed to create a
/// exchangeGameData object because runGame is the only object controlling it, an inputHandler Task to suspend and resume the possibility to shoot
/// and a weaponNumber which is initialized in the main().
/// After constructing the inputHanlder is suspended to prevent shooting and getting hit and the master is informed about this specific weapon beeing online.
runGame::runGame(display & Display, const playerData & player, hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBus, const long long int duration, rtos::task<> & handler, const uint8_t weaponNumber):
	Display(Display),
	player(player),
	exchanger(exchangeGameData(Display, this, spiBus, duration, weaponNumber)),
	secondClock(this, 1'000'000, "Second Clock for Timekeeping"),		//Secondclock fires every second
	receivedDataChannel(this, "Received Data Channel"),
	updateClockTimer(this, "Update Clock Timer"),
	handler(handler)
{
	handler.suspend();
	exchanger.signalOnline();
}

/// \brief
/// Get Player Data
/// \details
/// This function returns the current player with its current health and score. Needed for some objects that sometimes need the most updated player object.
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
	Display.showTime(remainingSeconds, gameSeconds);
	updateClockTimer.set((gameSeconds / 100 )* 1'000'000);
	Display.showHealthBar();
	Display.showFireMode(0);
	//Display.showScore(player.getScore());
}

/// \brief
/// Game Running Task
/// \details
/// This task has a couple of responsibilities. It should keep the time (hence the secondClock), determine when
/// the time should be displayed (this is dependent of the total game time) and changing the players health when
/// he is hit.
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
				Display.showHealth(player.getHealth());
				hwlib::cout << "New Health: " << player.getHealth() << hwlib::endl;
			}
		} else if (event == secondClock) {
			remainingSeconds--;
			if(remainingSeconds <= 0){
				handler.suspend();										//Prevent shooting after the time is up.
			}
		} else {
			Display.showTime(remainingSeconds);							//Update time on display every gameTime / 100 seconds; 
			updateClockTimer.set((gameSeconds / 100 )* 1'000'000);		//so time on display is updated 100 times during the entire game.
		}
	}
}

/// \brief
/// Constructor
/// \details
/// This function has several mandatory parameters. A display for the socreboard, a game to get temporary playerData, 
/// an SPI-Bus for the NRF24L01+, a duration that specifies the NRF24L01+'s poll period and a weaponNumber that's specified in the main().
exchangeGameData::exchangeGameData(display & Display, runGame * game, hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBus, const long long int duration, const uint8_t weaponNumber):
	Display(Display),
	game(game),
	weaponNumber(weaponNumber),
	radio(NRF24(spiBus, ce, csn, duration, game->getPlayerData().getPlayerNumber()))
{
	radio.addListener(this);
	receiveAddress[4] = game->getPlayerData().getPlayerNumber();			//Set receiveAddress to playernumber; hardcoded in each weapon.
}

/// \brief
/// Signal Online
/// \details
/// This function is used to let the master know this weapon is online. That's done by broadcasting a message of type 1
/// with the weaponNumber as the second byte.
void exchangeGameData::signalOnline(){
	radio.write_pipe( masterAddress );					//Master address = 0x00
   	radio.powerDown_rx();								//Enable TX mode

   	dataToTransmit[0] = 1;								//1 is defined as onlineMessage
   	dataToTransmit[1] = weaponNumber;					//Byte two should containt weaponNumber which also is the playerNumber
   	radio.write(dataToTransmit, amountOfDataToTransmit);

   	radio.read_pipe(startupAddress);					//Start listening to playerNumber address again.
   	radio.powerUp_rx();
}

/// \brief
/// Update Score
/// \details
/// When a player has been hit, the score to be added to the score of the shooter can be calculated.
/// After that's been done, the master should be notified of the shooter's new score. That's what this function is for.
/// The first parameter is equal to the first byte, the second parameter to the second byte.
void exchangeGameData::updateScore(const uint8_t playerNumber, const uint8_t dealtDamage){
	radio.write_pipe( masterAddress );				//Master address = 0x00
   	radio.powerDown_rx();							//Enable TX mode

   	dataToTransmit[0] = 2;							//2 is defined as newScoreMessage
   	dataToTransmit[1] = playerNumber;				//Byte two should contain the playerNumber of the shooter.
   	dataToTransmit[2] = dealtDamage;				//Byte three should containt the amount of dealt damage.
	radio.write( dataToTransmit, amountOfDataToTransmit );

   	radio.read_pipe(receiveAddress);				//Start listening to playerNumber address again.
   	radio.powerUp_rx();								//Enable RX Mode
}

/// \brief
/// Data Received
/// \details
/// This function has two parameters; the received data and the length of the data.
/// Based on the first received byte, the messageType can be determined.
/// Case 1 is a startGameMessage. The second byte is equal to the gameTime divided by ten
/// Case 2 is a newScore message.
/// Case 3 means that infiniteBUllets can be activated.
/// Case 4 means that instaDeath has been activated.
/// Case 6 means that a new player has signed up.
/// Case 7 means that all powerups have been disabled.
void exchangeGameData::dataReceived(const uint8_t data[], const int len){
	for(int i = 0; i < len; i++){
		hwlib::cout << data[i] << " ";
	}
	hwlib::cout << hwlib::endl;
	switch(data[0]){
		case 1:
			// for(int i = 0; i < signedUpPlayers; i++){
			// 	hwlib::cout << "Player " << board.playerNumbers[i] << ": ";
			// 	for(int j = 0; j < 8; j++){
			// 		hwlib::cout << board.playerNames[i][j];
			// 	}
			// 	hwlib::cout << hwlib::endl;
			// }
			game->gameStartSignalReceived(data[1]);
			break;
		case 2:
			if(data[1] == game->getPlayerData().getPlayerNumber()){
				game->getPlayerData().setScore(data[2]);
				Display.showScore(data[2]);
			}
			//What's happening here is just a start. Needs to be fixed; doesn't work.
			hwlib::cout << "Player";
			for(int i = 0; i < 31; i++){
				if(board.playerNumbers[i] == data[1]){
					for(int j = 0; j < 8; j++){
						hwlib::cout << board.playerNames[i][j];
					}
				}
			}

			hwlib::cout << " has a score of " << data[2] << " hence his position is " << data[3] << hwlib::endl;
			for(int i = 30; i > data[3]; i--){
				board.playerNumbers[i] = board.playerNumbers[i - i];
			}
			break;
		case 3:
			hwlib::cout << "InfiniteBullets Activated" << hwlib::endl;
			Display.showPowerUp(0);
			break;
		case 4:
			hwlib::cout << "InstaDeath Activated" << hwlib::endl;
			Display.showPowerUp(1);
			break;
		case 6:
			hwlib::cout << "PlayerNumber " << data[1] << " has name ";
			board.playerNumbers[signedUpPlayers] = data[1];
			for(int i = 2; i <= 10; i++){
				if(data[i] == 0){
					board.playerNames[signedUpPlayers][i - 2] = ' ';
				} else {
					board.playerNames[signedUpPlayers][i - 2] = char(data[i]);
				}
			}
			signedUpPlayers++;
			break;
		case 7:
			Display.showPowerUp(10);
			break;
		case 8:
			receiveAddress[4] = data[1];
			radio.read_pipe(receiveAddress);					//Start listening to playerNumber address again.
   			radio.powerUp_rx();
			break;
	}
}