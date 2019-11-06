#include "hwlib.hpp"
#include "RGBLed.hpp"

int main(){
	   auto sw = hwlib::target::pin_in( hwlib::target::pins::d4); 
	   hwlib::color initColor = hwlib::color(52, 112, 90);
	   hwlib::color healthColor = hwlib::color(0, 255, 0);
	   RGBLed Led = RGBLed(initColor);	  
	   int defaultLife =100;
		Led.setColor(healthColor);
	   for(;;){
		   healthColor.red = 255 - ((defaultLife * 25) / 10);
		   healthColor.green = (defaultLife * 25) / 10;

		   if(!sw.read()){
				Led.setColor(healthColor);
				defaultLife-=25;
			   hwlib::wait_ms(200);
		   }
	   }
}