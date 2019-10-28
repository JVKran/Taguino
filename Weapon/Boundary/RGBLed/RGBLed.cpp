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
{
      PMC-> PMC_PCER1 |= PMC_PCER1_PID36;                     // Enable PWM
  PIOA->PIO_ABSR |= PIO_ABSR_P19;                        // Set PWM pin perhipheral type A or B, in this case B
  PIOA->PIO_PDR |= PIO_PA19;
    PIOA->PIO_ABSR |= PIO_ABSR_P13;                        // Set PWM pin perhipheral type A or B, in this case B
  PIOA->PIO_PDR |= PIO_PA13;
      PIOC->PIO_ABSR |= PIO_ABSR_P9;                        // Set PWM pin perhipheral type A or B, in this case B
  PIOC->PIO_PDR |= PIO_PC9;
PWM->PWM_CH_NUM[1].PWM_CMR = PWM_CMR_CPRE_CLKA;
PWM->PWM_CH_NUM[2].PWM_CMR = PWM_CMR_CPRE_CLKA;  //PWM-> PWM_CMP[0];                          // Set PWM pin to an output
PWM->PWM_CH_NUM[3].PWM_CMR = PWM_CMR_CPRE_CLKA;
  PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42);     // Set the PWM clock rate to 2MHz (84MHz/42)

  //WM->PWM_CMR.CLAG = PWM_CMR_CALG; //| PWM_CMR_CPRE_CLKA;      // Enable dual slope PWM and set the clock source as CLKA
  PWM->PWM_CH_NUM[1].PWM_CPRD = 255;                                // Set the PWM frequency 2MHz/(2 * 20000) = 50Hz
  PWM->PWM_CH_NUM[1].PWM_CDTY = 1500;                                 // Set the PWM duty cycle to 1500 - centre the servo
  PWM->PWM_ENA = PWM_ENA_CHID1;                          // Enable the PWM channel   
    PWM->PWM_CH_NUM[2].PWM_CPRD = 255;                                // Set the PWM frequency 2MHz/(2 * 20000) = 50Hz
  PWM->PWM_CH_NUM[2].PWM_CDTY = 1500;                                 // Set the PWM duty cycle to 1500 - centre the servo
  PWM->PWM_ENA = PWM_ENA_CHID2;   
      PWM->PWM_CH_NUM[3].PWM_CPRD = 255;                                // Set the PWM frequency 2MHz/(2 * 20000) = 50Hz
  PWM->PWM_CH_NUM[3].PWM_CDTY = 255;                                 // Set the PWM duty cycle to 1500 - centre the servo
  PWM->PWM_ENA = PWM_ENA_CHID3;  
    setColor(color);}

void RGBLed::setColor(hwlib::color color){
    currentcolor = color;
    PWM->PWM_CH_NUM[2].PWM_CDTY = color.red;
    PWM->PWM_CH_NUM[3].PWM_CDTY = color.blue;
    PWM->PWM_CH_NUM[1].PWM_CDTY = color.green; 
    /*
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


