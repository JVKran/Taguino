#include "hwlib.hpp"
#include "entities.hpp"
#include "interface.hpp"
#include "scoreboard.hpp"
#include "input.hpp"
#include "weapon.hpp"
#include "game.hpp"
#include "display.hpp"
#include <array>

int main( void ){	
   hwlib::wait_ms( 500 );

   auto scl    = hwlib::target::pin_oc(hwlib::target::pins::scl);
   auto sda    = hwlib::target::pin_oc(hwlib::target::pins::sda);
   auto i2cBus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
   auto oled   = hwlib::glcd_oled(i2cBus);

   constexpr auto xCoordinates = lookup< int, 360>(scaled_sine_from_degrees);
   constexpr auto yCoordinates = lookup< int, 360>(scaled_cosine_from_degrees);

   //These values would usually be received from the master...
   const char * playerName = "Jochem";
   const int gameTime = 1000;
   const uint8_t playerNumber = 1;
   const uint8_t teamNumber = 1;

   const long long int infraredPollPeriod = 200;
   const long long int infraredTransmitPeriod = 200;
   const long long int inputPollPeriod = 100'000;

   playerData player = playerData(playerName, playerNumber, teamNumber);
   display Display = display(oled, xCoordinates, yCoordinates, gameTime);
   weaponData weapon = weaponData(2);
   runGame game = runGame(Display, player, gameTime);
   infraredDecoder decoder = infraredDecoder(game);
   infraredReceiver receiver = infraredReceiver(decoder, infraredPollPeriod);
   inputHandler handler = inputHandler(inputPollPeriod);                   //Period to poll register with buttonstates
   weaponManager gunManager = weaponManager(Display, handler, game, player, infraredTransmitPeriod);
   interfaceManager interface = interfaceManager(Display, handler, gunManager);

   rtos::run();
}
