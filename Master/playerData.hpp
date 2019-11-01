  
// this file contains Doxygen lines
/// @file

/// \brief
/// entity object playerData
/// \details
/// This object can be used to add players to the system

#ifndef __PLAYERDATA_HPP
#define __PLAYERDATA_HPP

#include "hwlib.hpp"

class playerData {
private:
	const char * name;
	const uint8_t playerNumber;
	const uint8_t teamNumber;
	uint8_t health = 100;
	uint16_t shots = 0;
	uint16_t damage = 0;
	uint8_t kills = 0;
	uint8_t deaths = 0;
	uint16_t score = 0;

public:

	/// \brief
    /// constructor
    /// \details
    /// This constructor does initialize the values name, playerNumber and teamNumber
	playerData(const char * name, const int playerNumber, const int teamNumber = 0);

	/// \brief
    /// get the name
    /// \details
    /// With this function you are able to read the name of the player
	const char * getName() const;

	/// \brief
    /// get the id number
    /// \details
    /// With this function you are able to read the id of the player
    /// this is usefull because this is what we use to send and receive data
    /// about the player
	uint8_t getPlayerNumber() const;

	/// \brief
    /// get the team number
    /// \details
    /// With this function you are able to read the team number of this player
	uint8_t getTeamNumber() const;

	/// \brief
    /// get the health
    /// \details
    /// With this function you are able to read what the current health is of the player
	uint8_t getHealth() const;

	/// \brief
    /// set the newHealth
    /// \details
    /// With this function you are able to set the new health of the player
	void setHealth(uint8_t newHealth);

	/// \brief
    /// get the shots that are fired
    /// \details
    /// With this function you are able to read the amount of bullets that have been shot
	uint16_t getShots() const;

	/// \brief
    /// add a shot
    /// \details
    /// This function when called will add one shot to the amount of bullets
	void setShots();

	/// \brief
    /// get the damage
    /// \details
    /// with this function you are able to read the amount of damage the player has dealth
    /// to other players
	uint16_t getDamage() const;

	/// \brief
    /// add damage
    /// \details
    /// This function will add damageDealt to damage
	void setDamage(uint8_t damageDealt);

	/// \brief
    /// get the amount of kills
    /// \details
    /// With this function you are able to read the amount of kills the player has made
	uint8_t getKills() const;

	/// \brief
    /// add a kill
    /// \details
    /// When this function is called it will add a kill to the total kills
	void setKills();

	/// \brief
    /// get the deaths
    /// \details
    /// return the amount of deaths from the player
	uint8_t getDeaths() const;

	/// \brief
    /// add a death
    /// \details
    /// when called this function will add a death to the players deaths
	void setDeaths();

	/// \brief
    /// get the score
    /// \details
    /// With this function you are able to read the total score of the player
	uint16_t getScore() const;

	/// \brief
    /// set the score
    /// \details
    /// this function adds score to the score of the player
	void setScore(uint8_t addScore);

	/// \brief
    /// write player to screen
    /// \details
    /// When cout is called with player it will show this long lap of data
	friend hwlib::ostream& operator<<(hwlib::ostream & stream, const playerData & player){
		stream << hwlib::left << "Statistics of player " << player.getName() << hwlib::endl;
		stream << hwlib::setw(30) << "Playernumber: " << player.getPlayerNumber() << hwlib::endl;
		stream << hwlib::setw(30) << "Team: " << player.getTeamNumber() << hwlib::endl;
		stream << hwlib::setw(30) << "Health: " << player.getHealth() << hwlib::endl;
		stream << hwlib::setw(30) << "Shots: " << player.getShots() << hwlib::endl;
		stream << hwlib::setw(30) << "Damage: " << player.getDamage() << hwlib::endl;
		stream << hwlib::setw(30) << "deaths: " << player.getDeaths() << hwlib::endl;
		stream << hwlib::setw(30) << "score: " << player.getScore() << hwlib::endl;
		stream << hwlib::setw(30) << "K/D: " << player.getKills() / player.getDeaths() << hwlib:;endl;
		return stream;
	}



};

#endif //__PLAYERDATA_HPP