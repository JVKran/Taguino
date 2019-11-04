#include "hwlib.hpp"
#include "entities.hpp"
#include "scoreboard.hpp"
#include "input.hpp"
#include "game.hpp"
#include "display.hpp"
#include "signup.hpp"
#include <array>

int main( void ){	
   hwlib::wait_ms( 500 );

   auto scl    = hwlib::target::pin_oc(hwlib::target::pins::scl);
   auto sda    = hwlib::target::pin_oc(hwlib::target::pins::sda);

   auto i2cBus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
   auto oled   = hwlib::glcd_oled(i2cBus);

   
   auto sclk = hwlib::target::pin_out( hwlib::target::pins::d9 );
   auto mosi = hwlib::target::pin_out( hwlib::target::pins::d12 );
   auto miso = hwlib::target::pin_in( hwlib::target::pins::d13 );
   auto csn  = hwlib::target::pin_out( hwlib::target::pins::d11 );
   auto ce   = hwlib::target::pin_out( hwlib::target::pins::d10 );

   auto spiBus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(sclk, mosi, miso);


   const long long int radioPollPeriod = 100;
   const uint8_t addressToListenTo = 0;
   NRF24 radio = NRF24(spiBus, ce, csn, radioPollPeriod, addressToListenTo);
   signUp signer = signUp(radio);
   game gameRunner = game(radio);
   radio.addListener(&signer);
   radio.addListener(&gameRunner);

   display Display = display(oled);
   oled.flush();
   rtos::run();
}
