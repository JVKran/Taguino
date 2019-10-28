#include "hwlib.hpp"
#include "RGBLed.hpp"

int main(){
   	hwlib::color kleur(255, 255, 255);

	//Wait for terminal
	hwlib::wait_ms(500);
    RGBLed Leeeed(kleur);
	for(;;){
        hwlib::wait_ms(1000);
        kleur.red =0;
        kleur.green=0;
        kleur.blue =255;
        Leeeed.setColor(kleur);
        hwlib::wait_ms(1000);
        kleur.red =255;
        kleur.green=0;
        kleur.blue =0;
        Leeeed.setColor(kleur);
        hwlib::wait_ms(1000);
        kleur.red =0;
        kleur.green=255;
        kleur.blue =0;
        Leeeed.setColor(kleur);
	}
}