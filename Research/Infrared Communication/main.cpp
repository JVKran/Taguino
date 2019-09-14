/*
#include "hwlib.hpp"


class transmitter : public hwlib::target::d2_36kHz {
private:
   hwlib::target::d2_36kHz transmitter = hwlib::target::d2_36kHz();
public:
   void sendBit(const bool bit){
      transmitter.set(1);
      hwlib::wait_us(800 * (1 + bit));
      transmitter.set(0);
      hwlib::wait_us(800 * (1 + !bit));
   }
};

//1SSSSSWWWAACCCCC
struct shotData{
   int playerNumber;
   int weaponType;
   int shotDistance;
   int dataControl = 0;
};




int main( void ){	

   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the PC terminal to start
   hwlib::wait_ms( 500 );

   auto irLed = transmitter();
   
   // when the switch is pressed, 
   // repeat sending 1 ms signal and 1 ms silence
   // and show this on the LED
   for(;;){
      
   }
}
*/


/*
#include "hwlib.hpp"

int main( void ){ 
    
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the PC terminal to start
   hwlib::wait_ms( 500 );
   
   // IR output LED
   due::pin_out transmitter = due::d2_36kHz();
   
   // red output LED
   auto red = hwlib::target::pin_out( hwlib::target::pins::d42 );
   
   
   // switch which enables the 36 kHz output
   auto sw = hwlib::target::pin_in( hwlib::target::pins::d43 );
   
   // when the switch is pressed, 
   // repeat sending 1 ms signal and 1 ms silence
   // and show this on the LED
   for(;;){
      hwlib::wait_ms( 1 ); 
      transmitter.set( ! sw.read() );
      red.write( ! sw.read() );
      
      hwlib::wait_ms( 1 );
      transmitter.set( 0 );
   }
}

*/

#include "hwlib.hpp"
#include "transmitter.hpp"


int main(){
   auto irLed = transmitter();
}


