/// @file

#include "hwlib.hpp"
#include "button.hpp"


Buttoninterrupter::Buttoninterrupter(){
    auto inputpin = hwlib::target::pin_in(hwlib::target::pins::a8);             //make pins input to prevent shorting arduino
    auto inputpin2 = hwlib::target::pin_in(hwlib::target::pins::a9);
    auto inputpin3 = hwlib::target::pin_in(hwlib::target::pins::a10);
    auto inputpin4 = hwlib::target::pin_in(hwlib::target::pins::a11);
    auto inputpin5 = hwlib::target::pin_in(hwlib::target::pins::dac0);    
    mask = 0x1U << 15;
    mask |= 0x1U << 17;                      // create mask to cover all pins
    mask |= 0x1U << 18;
    mask |= 0x1U << 19;
    mask |= 0x1U << 20;
    PIOB->PIO_IFER = mask;
    PIOB->PIO_DIFSR = mask;
    PIOB->PIO_IER = mask;                   //enable interrupts on pins
    PIOB->PIO_ESR = mask;                   //use edge detection
    PIOB->PIO_AIMER = mask;                 //use FELLSR for mode
}
void Buttoninterrupter::refreshregister(){
    registercont = PIOB->PIO_ISR;                   //take content of the interrupt status register and store it in registercont, needed because the registers clears on read
}


bool Buttoninterrupter::read(uint8_t pin){
    
    
    if((pin<21&&pin>16)||(pin==15)){                                     //check if button is within range
    return (( registercont & 0x1U << pin ) != 0 );          // read stored copy of the register for given button
    }
    else{
    return(0);
    hwlib::cout<<"nein";
    }
}
rotaryEncoder::rotaryEncoder(){
           
    // activate peripheral functions for quad pins
    PIOB->PIO_PDR = 1 << 25;     // activate peripheral function 
    PIOB->PIO_ABSR |= 1<<25;   // choose peripheral option B   
    PIOB->PIO_PDR = 1<<27;     // activate peripheral function 
    PIOB->PIO_ABSR |= 1<<27;   // choose peripheral option B
   
    // activate clock for TC0
     PMC->PMC_PCER0 = (1 << 27);
    // select XC0 as clock source and set capture mode
    TC0->TC_CHANNEL[0].TC_CMR = 5;
    // activate quadrature encoder and position measure mode, no filters
    TC0->TC_BMR = (1<<9)|(1<<8);
    // enable the clock (C) and reset the counter ()
    // SWTRG = 1 starts clock
    TC0->TC_CHANNEL[0].TC_CCR = 5;  
    }
int32_t rotaryEncoder::read(){
    return(int32_t(TC0->TC_CHANNEL[0].TC_CV));
}



