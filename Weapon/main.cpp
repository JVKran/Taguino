#include "hwlib.hpp"
#include "entities.hpp"

int main( void ){	
   hwlib::wait_ms( 500 );

   const char * playerName = "Jochem";
   playerData player = playerData(playerName, 1, 1);
   weaponData weapon = weaponData(4);

   hwlib::cout << player << hwlib::endl;

   hwlib::cout << weapon << hwlib::endl;

}
