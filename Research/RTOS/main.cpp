#include "hwlib.hpp"
#include "rtos.hpp"
#include "pause.hpp"
#include "message.hpp"

int main(){
   hwlib::wait_ms(500);
<<<<<<< HEAD
=======
   hwlib::cout<<"Runt dit uberhaupt\n";

>>>>>>> 6d246cd19dfe90c7b2fbbe3b372ee8b32b989ae8
   auto receiver = hwlib::target::pin_in( hwlib::target::pins::d5 );  

   auto logger = messageLogger("Message Logger"); 

   auto decoder = messageDecoder(logger);  
   
   auto detector = pauseDetector(receiver, decoder, 100, "Pause detecting task");

   hwlib::cout << "Jawoel" << hwlib::endl;
   
   rtos::run();
}