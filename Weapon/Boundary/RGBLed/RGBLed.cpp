/// @file

#include "hwlib.hpp"
#include "RGBLed.hpp"

/// \brief
/// Constructor
/// \details
/// This constructor takes one pin_out and one pin_in. These are the trig_pin and
/// echo_pin respectively.
RGBLed::RGBLed(hwlib::color color):
	currentcolor(color)
{setColor(color);}

void RGBLed::setColor(hwlib::color color){
    currentcolor = color;
    if(color.green>127){
        greenpin.write(0);
    }
    else
    {
        greenpin.write(1);
    }
    
    if(color.red>127){
        redpin.write(0);
    }
    else
    {
        redpin.write(1);
    }

    if(color.blue>127){
        bluepin.write(0);
    }
    else
    {
        bluepin.write(1);
    }
    /*
    
     // enable the clock to port A
	    PMC->PMC_PCER0 = 1 << ID_PIOA;
		
	    // disable PIO Control on PA10 and PA11 and set up for Peripheral A
		PIOA->PIO_PDR   = PIO_PA10; 
		PIOA->PIO_ABSR |= PIO_PA8;  


		// enable the clock to the USART
	    PMC->PMC_PCER0 = ( 0x01 << ID_PWM );

        PWM->PWM_WPCR = 0 << WPCMD;

	    // Reset and disable receiver and transmitter.
	    hw_usart->US_CR = US_CR_RSTRX | US_CR_RSTTX | US_CR_RXDIS | US_CR_TXDIS;

	    // Set the baudrate to 250 000.

	    hw_usart->US_BRGR = 21; 

	    // No parity, normal channel mode.
	    hw_usart->US_MR = US_MR_PAR_NO | US_MR_NBSTOP_2_BIT | US_MR_CHRL_8_BIT ;

	    // Disable all interrupts.	  
	    hw_usart->US_IDR = 0xFFFFFFFF;   

	    // Enable the receiver and the trasmitter.
	    hw_usart->US_CR = US_CR_RXEN | US_CR_TXEN;  
      */  
}


