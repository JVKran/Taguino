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

	playerData(const char * name, const int playerNumber, const int teamNumber = 0);

	const char * getName() const;
	uint8_t getPlayerNumber() const;
	uint8_t getTeamNumber() const;

	uint8_t getHealth() const;
	void setHealth(uint8_t damageDone);

	uint16_t getShots() const;
	void setShots();

	uint16_t getDamage() const;
	void setDamage(uint8_t damageDealt);

	uint8_t getKills() const;
	void setKills();

	uint8_t getDeaths() const;
	void setDeaths();

	uint16_t getScore() const;
	void setScore(uint8_t newShot);

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
