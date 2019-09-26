#include <hwlib.hpp>                                          //include hwlib to program for the arduino due

int main( void ){ 

   namespace target = hwlib::target;                          //so you don't have to write hwlib:: before target::...

   auto button = target::pin_in( hwlib::target::pins::d7 );   //button is on pin d7 of the arduino due
   bool check = true;                                         //a check to check if the button is pressed 1 time

   for(;;){                                                   //simple infinity loop to stay checking
    hwlib::wait_ms(50);                                       //wait 50 ms 
      if(button.read() == 1 && check == true){                //check if the button reads 1 and if check is true
         hwlib::cout << button.read() << "\n";                //show on the terminal if the button has been pressed
         check = false;                                       //set to false to make sure the button isn't pressed more times than intended to be
      } else if(button.read() == 0 && check == false){        //checks if the button reads 0 and if the check is false
         check = true;                                        //set the check to true again
      }
   }

}