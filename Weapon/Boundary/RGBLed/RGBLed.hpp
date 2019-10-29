#ifndef __RGB_LED_HPP
#define __RGB_LED_HPP
class RGBLed{
private:
    hwlib::color currentcolor;
    uint32_t mask;




public:
	RGBLed(hwlib::color color);
    void setColor(hwlib::color color);

	

};


#endif //__RGB_LED_HPP