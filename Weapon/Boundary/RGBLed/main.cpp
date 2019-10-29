#include "hwlib.hpp"
#include "RGBLed.hpp"

int main(){
   
   	hwlib::color kleur(0, 112, 255);
    RGBLed Leeeed(kleur);
    //Leeeed.startinterrupt();
/*
    for(;;){
 
        hwlib::cout<<"a9  "<<Leeeed.getinterrupt(uint32_t(0x1U << 17))<<hwlib::endl;
        hwlib::cout<<"a10  "<<Leeeed.getinterrupt(uint32_t(0x1U << 18))<<hwlib::endl;
        hwlib::cout<<"a11  "<<Leeeed.getinterrupt(uint32_t(0x1U << 19))<<hwlib::endl;
        hwlib::wait_ms(1000);
    }
    */
}