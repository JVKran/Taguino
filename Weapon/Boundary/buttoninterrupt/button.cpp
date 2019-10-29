/// @file

#include "hwlib.hpp"
#include "button.hpp"


Buttoninterrupter::Buttoninterrupter(){
    auto inputpin = hwlib::target::pin_in(hwlib::target::pins::a8);
    auto inputpin2 = hwlib::target::pin_in(hwlib::target::pins::a9);
    auto inputpin3 = hwlib::target::pin_in(hwlib::target::pins::a10);
    auto inputpin4 = hwlib::target::pin_in(hwlib::target::pins::a11);   
    mask = 0x1U << 17;
    mask |= 0x1U << 18;
    mask |= 0x1U << 19;
    mask |= 0x1U << 20;
    PIOB->PIO_IER = mask;
    PIOB->PIO_ESR = mask;
    PIOB->PIO_AIMER = mask;
    PIOB->PIO_FELLSR= mask;
    //return (( PIOC->PIO_ISR & mask ) != 0 );
}

bool Buttoninterrupter::getinterrupt1(){

    return (( PIOB->PIO_ISR & 0x1U << 17 ) != 0 );
}
bool Buttoninterrupter::getinterrupt2(){

    return (( PIOB->PIO_ISR & 0x1U << 18 ) != 0 );
}
bool Buttoninterrupter::getinterrupt3(){

    return (( PIOB->PIO_ISR & 0x1U << 19 ) != 0 );
}
bool Buttoninterrupter::getinterrupt4(){

    return (( PIOB->PIO_ISR & 0x1U << 20 ) != 0 );
}




