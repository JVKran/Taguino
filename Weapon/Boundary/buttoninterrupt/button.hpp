
#ifndef __BUTTON_REGISTER_HPP
#define __BUTTON_REGISTER_HPP


class buttonRegister {
private:
    uint32_t registercont;
    uint32_t mask;
    uint32_t doubleMask;
public:
    void refreshregister();
    bool read(uint8_t pin);

    buttonRegister();
};

class rotaryDecoder{
public:
    int32_t read();
    rotaryDecoder();
};

#endif //__BUTTON_REGISTER_HPP
