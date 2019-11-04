#include "hwlib.hpp"

class display{
private:
	hwlib::glcd_oled & oled;
	hwlib::window_part & terminalWindow;
	hwlib::terminal_from terminalScreen;
public:
	display(hwlib::glcd_oled & oled):
		oled(oled)
	{
		terminalWindow = hwlib::window_part(oled, hwlib::xy(0,0), hwlib::xy(128,64));
		terminalScreen = hwlib::terminal_from(terminalWindow, hwlib::font_default_8x8());
		terminalScreen << 6;
	}
};