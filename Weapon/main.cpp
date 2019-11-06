#include "hwlib.hpp"
#include "entities.hpp"
#include "interface.hpp"
#include "scoreboard.hpp"
#include "input.hpp"
#include "weapon.hpp"
#include "game.hpp"
#include "grenade.hpp"
#include "display.hpp"

#include <array>

int main( void ){	
   hwlib::wait_ms( 500 );

   auto scl    = hwlib::target::pin_oc(hwlib::target::pins::scl);
   auto sda    = hwlib::target::pin_oc(hwlib::target::pins::sda);

   auto i2cBus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
   hwlib::glcd_oled oled   = hwlib::glcd_oled(i2cBus);

   auto scoreFont      = hwlib::font_default_8x8();
   auto scoreWindow    = hwlib::window_part(oled, hwlib::xy(88, 9), hwlib::xy(128, 17));
   auto scoreBoardWindow    = hwlib::window_part(oled, hwlib::xy(0, 0), hwlib::xy(128, 64));
   auto scoreTerminal  = hwlib::terminal_from( scoreWindow, scoreFont );
   auto scoreBoardTerminal = hwlib::terminal_from( scoreBoardWindow, scoreFont );

   auto sclk = hwlib::target::pin_out( hwlib::target::pins::d24 );
   auto mosi = hwlib::target::pin_out( hwlib::target::pins::d26 );
   auto miso = hwlib::target::pin_in( hwlib::target::pins::d28 );
   auto csn  = hwlib::target::pin_out( hwlib::target::pins::d30 );
   auto ce   = hwlib::target::pin_out( hwlib::target::pins::d32 );

   auto spiBus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(sclk, mosi, miso);

   constexpr auto xCoordinates = lookup< int, 360>(scaled_sine_from_degrees);
   constexpr auto yCoordinates = lookup< int, 360>(scaled_cosine_from_degrees);

   //This one is device specific
   const uint8_t weaponNumber = 1;

   const long long int infraredPollPeriod = 200;
   const long long int infraredTransmitPeriod = 100;
   const long long int inputPollPeriod = 100'000;
   const long long int radioPollPeriod = 100'000;
   const long long int grenadePollPeriod = 100'000;
   HWLIB_TRACE;
   playerData player = playerData();
   HWLIB_TRACE;
   HWLIB_TRACE;
   display Display = display(oled, xCoordinates, yCoordinates, scoreWindow, scoreTerminal, scoreBoardTerminal);
   HWLIB_TRACE;
   weaponData weapon = weaponData(2);
   HWLIB_TRACE;
   inputHandler handler = inputHandler(inputPollPeriod);                   //Period to poll register with buttonstates
   HWLIB_TRACE;
   HWLIB_TRACE;

   HWLIB_TRACE;  
      //display Display = display(oled, xCoordinates, yCoordinates, scoreWindow, scoreTerminal, scoreBoardTerminal);
   HWLIB_TRACE;
      mhz433Read granaat(grenadePollPeriod); 
   HWLIB_TRACE;
   runGame game = runGame(Display, player, spiBus, radioPollPeriod, handler, weaponNumber, granaat);
   HWLIB_TRACE;
   infraredDecoder decoder = infraredDecoder(game);
   infraredReceiver receiver = infraredReceiver(decoder, infraredPollPeriod);
   infraredTransmitter Transmitter = infraredTransmitter(infraredTransmitPeriod);
   weaponManager gunManager = weaponManager(Display, handler, game, player, Transmitter);
   interfaceManager interface = interfaceManager(Display, handler, gunManager);
   HWLIB_TRACE;
   HWLIB_TRACE;
   rtos::run();
}
