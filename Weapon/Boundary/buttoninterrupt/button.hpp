
#ifndef __BUTTON_INTERRUPTER_HPP
#define __BUTTON_INTERRUPTER_HPP


class Buttoninterrupter{
private:
    hwlib::color currentcolor;
    uint32_t mask;




public:

    bool getinterrupt1();
    bool getinterrupt2();
    bool getinterrupt3();
    bool getinterrupt4();    
    Buttoninterrupter();

	

};

#endif //__BUTTON_INTERRUPTER_HPP
