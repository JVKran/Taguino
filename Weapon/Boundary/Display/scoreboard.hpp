#ifndef __SCOREBOARD_HPP
#define __SCOREBOARD_HPP

#include "hwlib.hpp"
#include "entities.hpp"
#include <array>

class scoreboard {
private:
	hwlib::window & window;
	hwlib::glcd_oled & oled;
	std::array<playerData, 5> & players;
public:
	scoreboard(hwlib::window & window, hwlib::glcd_oled & oled, std::array<playerData, 5> players);
};

#endif /* scoreboard.hpp */