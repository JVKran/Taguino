#include "scoreboard.hpp"

scoreboard::scoreboard(hwlib::window & window, hwlib::glcd_oled & oled, std::array<playerData, 5> players):
	window(window),
	oled(oled),
	players(players)
{}
