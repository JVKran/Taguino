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
public:
	scoreboard(	);
	std::array<std::array<char, 8>, 32> playerNames;
	std::array<uint8_t, 32> playerNumbers;
    std::array<uint8_t, 32> playerScores;
	void updateScoreBoard(const uint8_t data[5]);
	void printScoreboard();
	void setName(uint8_t pos,std::array<char,8> naam, int len );
};

#endif /* scoreboard.hpp */