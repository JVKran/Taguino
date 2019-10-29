
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

	

};

#endif //__BUTTON_INTERRUPTER_HPP
