#include "hwlib.hpp"
#include "entities.hpp"
#include "interface.hpp"
#include "input.hpp"
#include "weapon.hpp"
#include "game.hpp"
#include "display.hpp"
// #include "scoreboard.hpp"

int main( void ){	
   hwlib::wait_ms( 500 );

   auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
   auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
   auto i2cBus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
   auto oled = hwlib::glcd_oled(i2cBus);

   auto Display = display(oled);
   oled.clear();   
   oled.flush();

   auto window = hwlib::window_part(oled, hwlib::xy(0,0), hwlib::xy(128, 64));
   scoreboard bord = scoreboard(window, oled);
   oled.flush();

   const char * playerName = "Jochem";	//This would usually be received from the master...
   playerData player = playerData(playerName, 1, 1);
   weaponData weapon = weaponData(2);

   // hwlib::cout << player << hwlib::endl;

   // hwlib::cout << weapon << hwlib::endl;

   runGame game = runGame(player);
   inputHandler handler = inputHandler(100'000);
   weaponManager gunManager = weaponManager(handler, game);
   interfaceManager interface = interfaceManager(handler);

   rtos::run();
}
