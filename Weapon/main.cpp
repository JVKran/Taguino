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

   auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
   auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
   auto i2cBus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
   auto oled = hwlib::glcd_oled(i2cBus);
   constexpr auto xCoordinates = lookup< int, 360>(scaled_sine_from_degrees);
   constexpr auto yCoordinates = lookup< int, 360>(scaled_cosine_from_degrees);

   auto Display = display(oled, xCoordinates, yCoordinates);
   oled.clear();  
   oled.flush(); 
   Display.showTime(30, 60);
   Display.showBullets(9);
   Display.showWeapon(1);
   Display.showMagazines(9);
   Display.showHealthBar();
   Display.updateHealth(100,90);

   oled.flush();

   const char * playerName1 = "Jochem";	//This would usually be received from the master...
   playerData player1 = playerData(playerName1, 1, 1);
   weaponData weapon1 = weaponData(2);

   const char * playerName2 = "Stefan"; //This would usually be received from the master...
   playerData player2 = playerData(playerName2, 1, 1);
   weaponData weapon2 = weaponData(2);

   const char * playerName3 = "Joshua"; //This would usually be received from the master...
   playerData player3 = playerData(playerName3, 1, 1);
   weaponData weapon3 = weaponData(2);

   const char * playerName4 = "Faizal"; //This would usually be received from the master...
   playerData player4 = playerData(playerName4, 1, 1);
   weaponData weapon4 = weaponData(2);

   const char * playerName5 = "Menno"; //This would usually be received from the master...
   playerData player5 = playerData(playerName5, 1, 1);
   weaponData weapon5 = weaponData(2);

   // std::array<playerData,5> players = {player1, player2, player3, player4, player5};
   // auto window = hwlib::window_part(oled, hwlib::xy(0,0), hwlib::xy(128, 64));
   // scoreboard bord = scoreboard(window, oled, players);
   // oled.flush();


   runGame game = runGame(player1);
   inputHandler handler = inputHandler(100'000);
   weaponManager gunManager = weaponManager(Display, handler, game);
   interfaceManager interface = interfaceManager(handler);

   rtos::run();
}
