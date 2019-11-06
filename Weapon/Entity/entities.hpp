#ifndef __ENTITIES_HPP
#define __ENTITIES_HPP

#include "hwlib.hpp"
#include <array>

class playerData {
	private:
		char name[8];
		uint8_t playerNumber;
		int health = 100;
		int teamNumber;
		int score = 0;
		int shots = 0;
	public:

		const char * getName() const;
		void setName(const char newName[8]);

		uint8_t getPlayerNumber() const;
		void setPlayerNumber(const uint8_t newPlayerNumber);

		uint8_t getTeamNumber() const;
		void setTeamNumber(const uint8_t newTeamNumber);

		uint8_t getHealth() const;
		void setHealth(const int newHealth);

		uint8_t getScore() const;
		void setScore(const int newScore);

		uint8_t getShots() const;
		void setShots(const int newShots);

		friend hwlib::ostream& operator<<(hwlib::ostream & stream, const playerData & player){
			stream << hwlib::left << "Statistics of player " << player.getName() << hwlib::endl;
			stream << hwlib::setw(30) << "Playernumber: " << player.getPlayerNumber() << hwlib::endl;
			stream << hwlib::setw(30) << "Team: " << player.getTeamNumber() << hwlib::endl;
			stream << hwlib::setw(30) << "Health: " << player.getHealth() << hwlib::endl;
			stream << hwlib::setw(30) << "Average score per shot: " <<  int(player.getScore() / player.getShots()) << hwlib::endl;
			return stream;
		}
};

//WeaponSettings is only used by weaponData to lookup what settings are available. weaponData just calls the function with its ID.
//Hence it actually is another layer of abstraction; ApplicationLogic.
class weaponSettings {
	private:
		std::array<const char *, 5> weaponNames = 		{	"Shotgun", "Pistol", 	"Sniper", 	"AK-47", 	"M16"	};
		std::array<uint8_t, 5> damageFactors = 			{		65,		18, 		80, 		30, 		25		};
		std::array<uint8_t, 5> bulletsPerMag = 			{		4,		17, 		5, 			30, 		30		};
		std::array<uint8_t, 5> maxShotsPerTenSeconds = 	{		40, 	100, 		20,			100, 		140		};
		std::array<uint8_t, 5> amountOfMags = 			{		5,		2,			4,			3,			3		};
		std::array<bool, 5> autoAllowed = 				{		false, 	false, 		false, 		true, 		true	};
		std::array<bool, 5> burstAllowed = 				{		false, 	false, 		false, 		true, 		true	};
	public:
		const char * getName(const int weaponId) const;
		const int getDamage(const int weaponId, const int distance) const;
		const int getBulletsPerMag(const int weaponId) const;
		const int getAmountOfMags(const int weaponId) const;
		const int maxShotsPerTime(const int weaponId) const;
		const bool autoAllowedForWeapon(const int weaponId) const;
		const bool burstAllowedForWeapon(const int weaponId) const;
};

class weaponData {
	private:
		int id;
		int amountOfMags;
		int bulletAmount;

		weaponSettings weapons;
	public:
		weaponData(const int id = 0, const int amountOfMags = 0, const int bulletAmount = 0);

		int getId() const ;
		void setId(const int newId);

		int getAmountOfMags() const ;
		void setAmountOfMags(const int newAmount);

		unsigned int getAmountOfBullets() const;
		void setAmountOfBullets(const int newAmountOfBullets);

		const char * getName() const;
		const int getDamage(const int distance = 0) const;
		const int bulletsPerMag() const;
		const unsigned int maxShotsPerTenSeconds() const;
		const bool autoAllowed() const;
		const bool burstAllowed() const;

		friend hwlib::ostream& operator<<(hwlib::ostream & stream, const weaponData & weapon){
			stream << hwlib::left << "Statistics of weapon " << weapon.getName() << " with ID " << weapon.getId() << "." << hwlib::endl;
			stream << hwlib::setw(30) << "Bullets: " << weapon.getAmountOfBullets() << hwlib::endl;
			stream << hwlib::setw(30) << "Magazines: " << weapon.getAmountOfMags() << hwlib::endl;
			stream << hwlib::setw(30) << "Max shots per second: " << int(weapon.maxShotsPerTenSeconds() / 10) << hwlib::endl;
			stream << hwlib::setw(30) << "Burst Allowed: " << hwlib::boolalpha << weapon.burstAllowed() << hwlib::endl;
			stream << hwlib::setw(30) << "Auto Allowed: " << hwlib::boolalpha << weapon.autoAllowed() << hwlib::endl;
			stream << hwlib::setw(30) << "Damagefactor: " << hwlib::boolalpha << weapon.getDamage() << hwlib::endl;
			return stream;
		}
};

class displayedData {
	public:
		int lastBullets = 0;
		int lastMagazines =0;
		int lastHealth = 100;
		int lastScore = 0;
		int lastWeaponId = 0;
};

class scoreBoard {
public:
	std::array<char[8], 32> playerNames = {};
	std::array<uint8_t, 32> playerNumbers = {};
	std::array<uint8_t, 32> playerPositions = {};
	std::array<uint8_t, 32> playerScores = {};
};


#endif //__ENTITIES_HPP