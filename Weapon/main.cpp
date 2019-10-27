#include "hwlib.hpp"
#include "entities.hpp"
#include "input.hpp"
#include "weapon.hpp"
#include "game.hpp"

int main( void ){	
   hwlib::wait_ms( 500 );

   const char * playerName = "Jochem";	//This would usually be received from the master...
   playerData player = playerData(playerName, 1, 1);
   weaponData weapon = weaponData(2);

   hwlib::cout << player << hwlib::endl;

   hwlib::cout << weapon << hwlib::endl;

   runGame game = runGame(player);
   inputHandler handler = inputHandler();
   weaponManager gunManager = weaponManager(handler, game);

   rtos::run();

}
