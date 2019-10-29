/// @file

#include "hwlib.hpp"
#include "button.hpp"


Buttoninterrupter::Buttoninterrupter(){
    auto inputpin = hwlib::target::pin_in(hwlib::target::pins::a8);             //make pins input to prevent shorting arduino
    auto inputpin2 = hwlib::target::pin_in(hwlib::target::pins::a9);
    auto inputpin3 = hwlib::target::pin_in(hwlib::target::pins::a10);
    auto inputpin4 = hwlib::target::pin_in(hwlib::target::pins::a11);   
    mask = 0x1U << 17;                      // create mask to cover all pins
    mask |= 0x1U << 18;
    mask |= 0x1U << 19;
    mask |= 0x1U << 20;
    PIOB->PIO_IFER = mask;
    PIOB->PIO_DIFSR = mask;
    PIOB->PIO_IER = mask;                   //enable interrupts on pins
    PIOB->PIO_ESR = mask;                   //use edge detection
    PIOB->PIO_AIMER = mask;                 //use FELLSR for mode
    PIOB->PIO_FELLSR= mask;                 //mode :: falling edge
    //return (( PIOC->PIO_ISR & mask ) != 0 );
}
void Buttoninterrupter::refreshregister(){
    registercont = PIOB->PIO_ISR;                   //take content of the interrupt status register and store it in registercont, needed because the registers clears on read
    //registercont = PIOB->PIO_AIMMR;
}


bool Buttoninterrupter::read(uint8_t pin){
    
    
    if(pin<21&&pin>16){                                     //check if button is within range
    return (( registercont & 0x1U << pin ) != 0 );          // read stored copy of the register for given button
    }
    else{
    return(0);
    hwlib::cout<<"nein";
    }
}



