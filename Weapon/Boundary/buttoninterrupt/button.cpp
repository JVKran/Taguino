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
    PIOB->PIO_IER = mask;                   //enable interrupts on pins
    PIOB->PIO_ESR = mask;                   //use edge detection
    PIOB->PIO_AIMER = mask;                 //use FELLSR for mode
    PIOB->PIO_FELLSR= mask;                 //mode :: falling edge
    //return (( PIOC->PIO_ISR & mask ) != 0 );
}
void Buttoninterrupter::getregister(){
    registercont = PIOB->PIO_ISR;
}


bool Buttoninterrupter::getinterrupt1(){

    //return (( PIOB->PIO_ISR & 0x1U << 17 ) != 0 );          // read interrupt register for button
    return (( registercont & 0x1U << 17 ) != 0 );          // read interrupt register for button
}
bool Buttoninterrupter::getinterrupt2(){

    return (( registercont & 0x1U << 18 ) != 0 );          // read interrupt register for button
}
bool Buttoninterrupter::getinterrupt3(){

    return (( registercont & 0x1U << 19 ) != 0 );          // read interrupt register for button
}
bool Buttoninterrupter::getinterrupt4(){

    return (( registercont & 0x1U << 20 ) != 0 );          // read interrupt register for button
}




