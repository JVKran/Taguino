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
	
	hwlib::cout<<"Delete gameStartSignalReceived(100);"<<hwlib::endl;
	// gameStartSignalReceived(100);
	hwlib::cout<<"Delete gameStartSignalReceived(100);"<<hwlib::endl;
	
}

/// \brief
/// Get Player Data
/// \details
/// This function returns the current player with its current health and score. Needed for some objects that sometimes need the most updated player object.
playerData runGame::getPlayerData() const {
	return player;
}

void runGame::setPlayerData(playerData & newPlayer){
	player = newPlayer;
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
			playerNumber = (receivedData >> 10);
			if(playerNumber != player.getPlayerNumber() && player.getHealth() > 0){			//If player didn't shoot himself
				distance = (receivedData & 0x3F) * 10;
				weaponId = ((receivedData & 0x1C0) >> 6);
				dealtDamage = weaponStats.getDamage(weaponId, distance);
				// hwlib::cout << "Player " << playerNumber << " shot us from a distance of " << distance << " with weapon " << weaponId << '.' << hwlib::endl;
				// hwlib::cout << "This is equal to a damage of " << dealtDamage << ". " << hwlib::endl;
				// hwlib::cout << "Hence our new health is " << player.getHealth() << '.' << hwlib::endl;
				exchanger.updateScore(playerNumber, dealtDamage);
				player.setHealth(player.getHealth() - dealtDamage);
				if(player.getHealth() < 0){
					player.setHealth(0);
				}
				Display.showHealth(player.getHealth());
				healthColor.red = (player.getHealth() * 25) / 10;
				healthColor.green = 255 - ((player.getHealth() * 25) / 10);
				Led.setColor(healthColor);
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
void exchangeGameData::dataReceived(uint8_t data[10], const int len){
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
			hwlib::cout << "Game started with a game duration of " << data[1] * 10 << " seconds!" << hwlib::endl;
			break;
		case 2:
			if(data[1] == game->getPlayerData().getPlayerNumber()){
				game->getPlayerData().setScore(data[2]);
				Display.showScore(data[2]);
			}
			Display.Scoreboard.updateScoreBoard(data);

			// for(int i = 0; i < 32; i++){
			// 	if(board.playerNumbers[i] == data[1]){
			// 		board.playerScores[i] += data[2];
			// 		break;
			// 	}
			// 	if(i == 31){
			// 		for(int i = 0; i < 31; i++){
			// 			if(board.playerScores[i] < data[2]){
			// 				for(int j = 32; j >= i; j--){
			// 					board.playerScores[j] = board.playerScores[j - 1];
			// 					board.playerNumbers[j] = board.playerNumbers[j - 1];
			// 				}
			// 				board.playerScores[i] = data[2];
			// 				board.playerNumbers[i] = data[1];
			// 				break;
			// 			}
			// 		}
			// 	}
			// }
			bubbleSort(Display.Scoreboard.playerNumbers, Display.Scoreboard.playerScores,30);
			Display.Scoreboard.updateScoreBoard(data);
			// hwlib::cout << "Playernumber\t\t\tScore" << hwlib::endl;
			// for(int i = 0; i < 31; i++){
			// 	hwlib::cout << int(board.playerNumbers[i]) << "\t\t\t" << int(board.playerScores[i]) << hwlib::endl;
   //      		}
			// break;
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
			hwlib::cout << "All power-ups have been disabled!" << hwlib::endl;
			break;
		case 8:
			if(startupAddress[4] == 100){
				hwlib::cout << "Received address " << data[1] << "!" << hwlib::endl;
				receiveAddress[4] = data[1];
				radio.read_pipe(receiveAddress);					//Start listening to playerNumber address again.
	   			radio.powerUp_rx();
	   			player = game->getPlayerData();
	   			player.setPlayerNumber(data[1]);
	   			game->setPlayerData(player);
	   			startupAddress[4] = 0;
			}
			break;
	}
}
