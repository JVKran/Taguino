/// @file

#include "hwlib.hpp"
#include "RGBLed.hpp"

/// \brief
/// Constructor
/// \details
/// this constructor takes a color and initalises an RGB led and then sets it to that color
RGBLed::RGBLed(hwlib::color color):
	currentcolor(color)
{
  PMC-> PMC_PCER1 |= PMC_PCER1_PID36;                     // Enable PWM
  PIOA->PIO_ABSR |= PIO_ABSR_P19;                        // Set PWM pins perhipheral B
  PIOA->PIO_PDR |= PIO_PA19;                             // Set PWM pins as output
  PIOA->PIO_ABSR |= PIO_ABSR_P13;                        
  PIOA->PIO_PDR |= PIO_PA13;
  PIOC->PIO_ABSR |= PIO_ABSR_P9;                        
  PIOC->PIO_PDR |= PIO_PC9;




PWM->PWM_CH_NUM[1].PWM_CMR = PWM_CMR_CPRE_CLKA;         //set PWM prescaler to clock(84mhz)
PWM->PWM_CH_NUM[2].PWM_CMR = PWM_CMR_CPRE_CLKA;                          
PWM->PWM_CH_NUM[3].PWM_CMR = PWM_CMR_CPRE_CLKA;

  PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(22);     // Set the PWM clock rate to 2MHz (prescaler 84MHz/42)


  PWM->PWM_CH_NUM[1].PWM_CPRD = 255;                                // Set the PWM frequency 2MHz/(2 * 255) = 3.9kHz
  PWM->PWM_CH_NUM[1].PWM_CDTY = 255;                                 // Set the PWM duty cycle to 255 max
  PWM->PWM_ENA = PWM_ENA_CHID1;                          // Enable the PWM channel   
    PWM->PWM_CH_NUM[2].PWM_CPRD = 255;                                
  PWM->PWM_CH_NUM[2].PWM_CDTY = 255;                                 
  PWM->PWM_ENA = PWM_ENA_CHID2;   
      PWM->PWM_CH_NUM[3].PWM_CPRD = 255;
  PWM->PWM_CH_NUM[3].PWM_CDTY = 255;                                 
  PWM->PWM_ENA = PWM_ENA_CHID3;  
    setColor(color);}

void RGBLed::setColor(hwlib::color color){
    currentcolor = color;
    PWM->PWM_CH_NUM[2].PWM_CDTY = color.red;                //Takes red value and puses it to the output register
    PWM->PWM_CH_NUM[3].PWM_CDTY = color.blue;               //Takes blue value and puses it to the output register
    PWM->PWM_CH_NUM[1].PWM_CDTY = color.green;              //Takes green value and puses it to the output register

}


