#include "hwlib.hpp"
#include "rtos.hpp"
#include "pause.hpp"

int main(){
   auto receiver = hwlib::target::pin_in( hwlib::target::pins::d7 );      
   
   auto p = pauseDetector(receiver, 100, "Pause detecting task");
   
   rtos::run();
}