#ifndef __SCOREBOARD_HPP
#define __SCOREBOARD_HPP

#include "hwlib.hpp"
#include "entities.hpp"
#include "applicationLogic.hpp"
#include <array>

class scoreboard {
private:
	hwlib::terminal & scoreTerminal;
public:
	scoreboard(hwlib::terminal & scoreTerminal);
	std::array<uint8_t, 32> playerNumbers;
    std::array<uint8_t, 32> playerScores;
	void updateScoreBoard(uint8_t data[5]);
	void printScoreboard();
};

#endif /* scoreboard.hpp */