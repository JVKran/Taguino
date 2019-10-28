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

   /*
     // PWM Set-up on pin: DAC1
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

   for(;;){
       for(int i=0; i<254; i++){
       hwlib::wait_ms(10);
      PWM->PWM_CH_NUM[2].PWM_CDTY = i; 

       }
              for(int i=0; i<254; i++){
       hwlib::wait_ms(10);
      PWM->PWM_CH_NUM[1].PWM_CDTY = i; 

       }
                     for(int i=0; i<254; i++){
       hwlib::wait_ms(10);
      PWM->PWM_CH_NUM[3].PWM_CDTY = i; 

       }
   */    


}