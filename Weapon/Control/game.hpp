#ifndef __GAME_HPP
#define __GAME_HPP

#include "entities.hpp"
#include "receiver.hpp"
#include "NRF24.hpp"
#include "RGBLed.hpp"
#include "display.hpp"
#include "rtos.hpp"

class runGame;

class exchangeGameData : public radioListener {
private:
  display & Display;
  runGame * game;

  playerData player;

  const uint8_t weaponNumber;

  scoreBoard board;
  int signedUpPlayers = 0;

  //Used for the NRF24L01+
  hwlib::target::pin_out csn  = hwlib::target::pin_out( hwlib::target::pins::d30 );
  hwlib::target::pin_out ce   = hwlib::target::pin_out( hwlib::target::pins::d32 );

  NRF24 radio;
  uint8_t dataToTransmit[5] = {0, 0, 0, 0, 0};    //Used for storing data to transmit
  uint8_t receiveAddress[5] = {0, 0, 0, 0, 0};    //Used to store the address at which to listen for incoming messages
  uint8_t startupAddress[5] = {0,0, 0, 0, 100};

  uint8_t masterAddress[5] = {0, 0, 0, 0, 0};     //Used to store the address of the master
  const uint8_t amountOfDataToTransmit = 5;       //Contains the length of the data to transmit; always 5.
public:
  exchangeGameData(display & Display, runGame * game, hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBus, const long long int duration, const uint8_t weaponNumber);

  virtual void dataReceived(const uint8_t data[10], const int len) override;

  void updateScore(const uint8_t playerNumber, const uint8_t dealtDamage);
  void signalOnline();

};

class runGame : public messageListener, public rtos::task<> {
private:
  display & Display;
  playerData player;

  RGBLed Led = RGBLed();

  uint16_t receivedData;
  exchangeGameData exchanger;

  uint8_t distance;
  uint8_t playerNumber;
  uint8_t weaponId;
  uint8_t dealtDamage;

  weaponSettings weaponStats = weaponSettings();

  rtos::clock secondClock;                           //Activates main() every second to substract 1 from remainingTime.
  int gameSeconds;                                   //After initialization remainingSeconds and gameSeconds are equal.
  int remainingSeconds;

  rtos::channel<uint16_t, 10> receivedDataChannel;   //Contains received Infrared Messages.
  rtos::timer updateClockTimer;

  rtos::task<> & handler;

public:
  runGame(display & Display, const playerData & player, hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBus, const long long int duration, rtos::task<> & handler, const uint8_t weaponNumber);
  
  playerData getPlayerData() const;                         //Used by weaponManager to get playerNumber for infraredMessage.
  void setPlayerData(playerData & newPlayer);

  virtual void messageReceived(const uint16_t data);

  void gameStartSignalReceived(const uint8_t timeToPlay);

  void main() override;
};


#endif //__GAME_HPP