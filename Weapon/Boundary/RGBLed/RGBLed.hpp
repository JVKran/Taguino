#ifndef __BUTTON_INTERRUPTER_HPP
#define __BUTTON_INTERRUPTER_HPP

class RGBLed{
private:
    hwlib::color currentcolor;
    uint32_t mask;
    //hwlib::target::pin_in inputpin;



public:
	RGBLed(hwlib::color color);
    void setColor(hwlib::color color);
    //bool getinterrupt(uint32_t masker);
    //void startinterrupt();

	

};


#endif //__BUTTON_INTERRUPTER_HPP