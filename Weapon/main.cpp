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
   const int gameTime = 1001;
   const uint8_t playerNumber = 1;
   const uint8_t teamNumber = 1;

   display Display = display(oled, xCoordinates, yCoordinates, gameTime);
   playerData player = playerData(playerName, playerNumber, teamNumber);
   weaponData weapon = weaponData(2);
   runGame game = runGame(Display, player, gameTime, 100'000);    //Period to check for IR signals
   inputHandler handler = inputHandler(100'000);               //Period to poll register
   weaponManager gunManager = weaponManager(Display, handler, game, player);
   interfaceManager interface = interfaceManager(Display, handler, gunManager);

   rtos::run();
}
