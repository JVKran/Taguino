#ifndef __RGB_LED_HPP
#define __RGB_LED_HPP

class Buttoninterrupter{
private:
    hwlib::color currentcolor;
    uint32_t mask;
    //hwlib::target::pin_in inputpin;



public:

    bool getinterrupt1();
    bool getinterrupt2();
    bool getinterrupt3();
    bool getinterrupt4();    
    Buttoninterrupter();

	

};


#endif //__RGB_LED_HPP