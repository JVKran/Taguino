#include "hwlib.hpp"
#include "entities.hpp"
#include "interface.hpp"
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

   auto Display = display(oled, xCoordinates, yCoordinates);
   oled.clear();  
   oled.flush(); 
   // Display.showTime(15, 60);
   // Display.showBullets(12);
   // Display.showWeapon(0);
   // Display.showMagazines(1);
   // Display.showHealthBar();
   // Display.updateHealth(100,72);

   Display.showPowerUp(1);
   oled.flush();

   const char * playerName1 = "Jochem";	//This would usually be received from the master...
   playerData player1 = playerData(playerName1, 1, 1);
   weaponData weapon1 = weaponData(2);

   runGame game = runGame(player1);
   inputHandler handler = inputHandler(100'000);
   weaponManager gunManager = weaponManager(Display, handler, game);
   interfaceManager interface = interfaceManager(handler);

   rtos::run();
}
