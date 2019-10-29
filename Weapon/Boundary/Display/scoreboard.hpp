#ifndef __SCOREBOARD_HPP
#define __SCOREBOARD_HPP

#include "hwlib.hpp"

class scoreboard{
private:
	hwlib::window & window;
	hwlib::glcd_oled & oled;
public:
	scoreboard(hwlib::window & window, hwlib::glcd_oled & oled);
};

class scoreboardLine{
private:
	hwlib::window & nameWindow;
	hwlib::window & scoreWindow;
public:
	scoreboardLine(hwlib::window & nameWindow, hwlib::window & scoreWindow);
};
#endif /* scoreboard.hpp */