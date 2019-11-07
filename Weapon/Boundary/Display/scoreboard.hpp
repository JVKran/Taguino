/// @file

#ifndef __SCOREBOARD_HPP
#define __SCOREBOARD_HPP

#include "hwlib.hpp"
#include "entities.hpp"
#include "applicationLogic.hpp"
#include <array>

/// \brief
/// Scoreboard
/// \details
/// This class is used to keep and print the scoreboard.
class scoreboard {
private:
	hwlib::terminal & scoreTerminal;
	display * Display;
public:
	scoreboard(hwlib::terminal & scoreTerminal, display * Display);
	std::array<uint8_t, 32> playerNumbers;
    std::array<uint8_t, 32> playerScores;
	void updateScoreBoard(uint8_t data[5]);
	void printScoreboard();
};

#endif /* scoreboard.hpp */