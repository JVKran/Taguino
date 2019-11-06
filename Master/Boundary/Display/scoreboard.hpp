/*

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

#endif scoreboard.hpp 

*/


#ifndef __SCOREBOARD_HPP
#define __SCOREBOARD_HPP

#include "hwlib.hpp"
#include "entities.hpp"
#include "applicationLogic.hpp"
#include <array>

class scoreboard {
private:
	
public:
	scoreboard(	);
	std::array<uint8_t, 32> playerNumbers;
    std::array<uint8_t, 32> playerScores;
	void updateScoreBoard(const uint8_t data[5]);
	void printScoreboard();
};

#endif /* scoreboard.hpp */