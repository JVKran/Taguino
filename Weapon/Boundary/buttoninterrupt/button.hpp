/// @file

#ifndef __BUTTON_REGISTER_HPP
#define __BUTTON_REGISTER_HPP


/// \brief
/// Button Register
/// \details
/// This class is used to refresh the values in the desired register. This can be useful
/// to determine wether or not a button has been pressed.
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

/// \brief
/// Rotary Decoder
/// \details
/// This class is used to enable the Quadrature Decoder built in the Atmel chip. Futhermore,
/// the position can be read from the register.
class rotaryDecoder{
public:
    int32_t read();
    rotaryDecoder();
};

#endif //__BUTTON_REGISTER_HPP
