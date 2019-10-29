
#ifndef __BUTTON_INTERRUPTER_HPP
#define __BUTTON_INTERRUPTER_HPP


class Buttoninterrupter{
private:
    uint32_t registercont;
    uint32_t mask;




public:
    void getregister();
    bool getinterrupt1();           //read the interrupt register
    bool getinterrupt2();          // read interrupt register for button
    bool getinterrupt3();          // read interrupt register for button
    bool getinterrupt4();          // read interrupt register for button    
    Buttoninterrupter();           // constructor

	

};

#endif //__BUTTON_INTERRUPTER_HPP
