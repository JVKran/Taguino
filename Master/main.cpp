#include "hwlib.hpp"
#include "entities.hpp"
#include "scoreboard.hpp"
#include "input.hpp"
#include "game.hpp"
#include "display.hpp"
#include "interface.hpp"
#include "signup.hpp"
#include "scoreboard.hpp"
#include <array>

int main( void ){	
   hwlib::wait_ms( 500 );

   auto scl    = hwlib::target::pin_oc(hwlib::target::pins::scl);
   auto sda    = hwlib::target::pin_oc(hwlib::target::pins::sda);
   auto i2cBus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
   auto oled   = hwlib::glcd_oled(i2cBus);

   constexpr auto xCoordinates = lookup< int, 360>(scaled_sine_from_degrees);
   constexpr auto yCoordinates = lookup< int, 360>(scaled_cosine_from_degrees);
   auto scoreFont      = hwlib::font_default_8x8();
   auto scoreWindow    = hwlib::window_part(oled, hwlib::xy(88, 9), hwlib::xy(128, 17));
   auto scoreTerminal  = hwlib::terminal_from( scoreWindow, scoreFont );

   auto sclk = hwlib::target::pin_out( hwlib::target::pins::d9 );
   auto mosi = hwlib::target::pin_out( hwlib::target::pins::d12 );
   auto miso = hwlib::target::pin_in( hwlib::target::pins::d7 );
   auto csn  = hwlib::target::pin_out( hwlib::target::pins::d11 );
   auto ce   = hwlib::target::pin_out( hwlib::target::pins::d10 );

   auto spiBus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(sclk, mosi, miso);

   const long long int radioPollPeriod = 100'000;
   const uint8_t addressToListenTo = 0;
   const long long int inputPollPeriod = 100'000;

   NRF24 radio = NRF24(spiBus, ce, csn, radioPollPeriod, addressToListenTo);
   display Display = display(oled, xCoordinates, yCoordinates, scoreWindow, scoreTerminal);
      scoreboard bord;
      bord.printScoreboard();

   game gameRunner = game(Display, radio,bord);
   inputHandler handler = inputHandler(inputPollPeriod);
   signUp signer = signUp(radio,handler,gameRunner, bord); 
   interfaceManager interface = interfaceManager(Display, handler, signer, gameRunner);
   radio.addListener(&signer);
   radio.addListener(&gameRunner);
   HWLIB_TRACE;
   rtos::run();
}
