#include "hwlib.hpp"
#include "rtos.hpp"
#include "pause.hpp"
#include "message.hpp"

int main(){
   hwlib::wait_ms(500);
   hwlib::cout<<"Runt dit uberhaupt\n";

   auto receiver = hwlib::target::pin_in( hwlib::target::pins::d5 );  

   auto logger = messageLogger("Message Logger"); 

   auto decoder = messageDecoder(logger);  
   
   auto detector = pauseDetector(receiver, decoder, 100, "Pause detecting task");
   
   rtos::run();
}