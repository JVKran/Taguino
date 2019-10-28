#ifndef __RGB_LED_HPP
#define __RGB_LED_HPP

class RGBLed{
private:
    hwlib::color currentcolor;
	hwlib::target::pin_out redpin = hwlib::target::pin_out(hwlib::target::pins::d30);
	hwlib::target::pin_out bluepin = hwlib::target::pin_out(hwlib::target::pins::d31);
    hwlib::target::pin_out greenpin = hwlib::target::pin_out(hwlib::target::pins::d32);


public:
	RGBLed(hwlib::color color);
    void setColor(hwlib::color color);

	

};


#endif //__RGB_LED_HPP