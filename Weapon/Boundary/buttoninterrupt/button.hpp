
#ifndef __BUTTON_INTERRUPTER_HPP
#define __BUTTON_INTERRUPTER_HPP


class Buttoninterrupter{
private:
    uint32_t registercont;
    uint32_t mask;




public:
    void refreshregister();            //store a copy of the register content, needed because the register clears on read
    bool read(uint8_t pin);           //read the stored copy of the interrupt register for pin i

    Buttoninterrupter();           // constructor


/*
const int quad_A = 2;
const int quad_B = 13;
const unsigned int mask_quad_A = digitalPinToBitMask(quad_A);
const unsigned int mask_quad_B = digitalPinToBitMask(quad_B); 

void setup() {
    Serial.begin(115200); 
    delay(100);
   
    // activate peripheral functions for quad pins
    PIOB->PIOB_PDR = mask_quad_A;     // activate peripheral function (disables all PIO functionality)
    PIOB->PIOB_ABSR |= mask_quad_A;   // choose peripheral option B   
    PIOB->PIOB_PDR = mask_quad_B;     // activate peripheral function (disables all PIO functionality)
    PIOB->PIOB_ABSR |= mask_quad_B;   // choose peripheral option B
   
    // activate clock for TC0
     PMC->PMC_PCER0 = (1 << 28);
    // select XC0 as clock source and set capture mode
    TC0->TC_CHANNEL[0].TC_CMR = 5;
    // activate quadrature encoder and position measure mode, no filters
    REG_TC0_BMR = (1<<9)|(1<<8);
    // enable the clock (CLKEN=1) and reset the counter (SWTRG=1)
    // SWTRG = 1 necessary to start the clock!!
    REG_TC0_CCR0 = 5;   
   
void loop() {
  Serial.println(REG_TC0_CV0,DEC);
  delay(500);
}
	
*/
};

#endif //__BUTTON_INTERRUPTER_HPP
