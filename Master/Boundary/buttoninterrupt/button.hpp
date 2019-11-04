
#ifndef __BUTTON_INTERRUPTER_HPP
#define __BUTTON_INTERRUPTER_HPP


class Buttoninterrupter{
private:
    uint32_t registercont;
    uint32_t mask;
    uint32_t mask2;
public:
    void refreshregister();
    bool read(uint8_t pin);

    Buttoninterrupter();
};

class rotaryEncoder{
    public:
    int32_t read();
    rotaryEncoder();
};

#endif //__BUTTON_INTERRUPTER_HPP
