#include "hwlib.hpp"
#include "rtos.hpp"
#include "pause.hpp"
#include "message.hpp"

int main(){
   hwlib::wait_ms(500);

   auto scl      = hwlib::target::pin_oc{ hwlib::target::pins::scl };
   auto sda      = hwlib::target::pin_oc{ hwlib::target::pins::sda };
   
   auto i2c_bus  = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );

   auto receiver = hwlib::target::pin_in( hwlib::target::pins::d5 );  

   auto logger = messageLogger(i2c_bus, "Message logging task"); 

   auto decoder = messageDecoder(logger);  
   
   auto detector = pauseDetector(receiver, decoder, 100, "Pause detecting task");

   HWLIB_TRACE;
   
   rtos::run();
}