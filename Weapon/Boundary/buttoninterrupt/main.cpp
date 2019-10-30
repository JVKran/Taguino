#include "hwlib.hpp"
#include "button.hpp"

int main(){
    
    Buttoninterrupter knoppen;
    rotaryEncoder draaier;

    hwlib::wait_ms(500);
    for(;;){
        knoppen.refreshregister();
        hwlib::cout<<hwlib::endl<<"a9  "<<knoppen.read(17)<<hwlib::endl;
        hwlib::cout<<hwlib::endl<<"a10 "<<knoppen.read(18)<<hwlib::endl;
        hwlib::cout<<hwlib::endl<<"a11 "<<knoppen.read(19)<<hwlib::endl;
        hwlib::cout<<hwlib::endl<<"a12 "<<knoppen.read(20)<<hwlib::endl;
        hwlib::cout<<hwlib::endl<<"b15 "<<knoppen.read(15)<<hwlib::endl;
        hwlib::cout<<hwlib::endl<<"enc "<<draaier.read()<<hwlib::endl;    
        hwlib::wait_ms(1000);
    }
    /*
    hwlib::wait_ms(500);
   
    // activate peripheral functions for quad pins
    PIOB->PIO_PDR = 1 << 25;     // activate peripheral function (disables all PIO functionality)
    PIOB->PIO_ABSR |= 1<<25;   // choose peripheral option B   
    PIOB->PIO_PDR = 1<<27;     // activate peripheral function (disables all PIO functionality)
    PIOB->PIO_ABSR |= 1<<27;   // choose peripheral option B
   
    // activate clock for TC0
     PMC->PMC_PCER0 = (1 << 27);
    // select XC0 as clock source and set capture mode
    TC0->TC_CHANNEL[0].TC_CMR = 5;
    // activate quadrature encoder and position measure mode, no filters
    TC0->TC_BMR = (1<<9)|(1<<8);
    // enable the clock (CLKEN=1) and reset the counter (SWTRG=1)
    // SWTRG = 1 necessary to start the clock!!
    TC0->TC_CHANNEL[0].TC_CCR = 5;   
   
for(;;){
  hwlib::cout<<int32_t(TC0->TC_CHANNEL[0].TC_CV)<<hwlib::endl;
  hwlib::wait_ms(500);
}
*/
}