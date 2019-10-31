#ifndef __ENTITIES_HPP
#define __ENTITIES_HPP

#include "hwlib.hpp"
#include <array>

class playerData {
	private:
		const char * name;
		const int playerNumber;
		int health = 100;
		const int teamNumber;
		int score = 0;
		int shots = 0;
	public:
		playerData(const char * name, const int playerNumber, const int teamNumber = 0);

		const char * getName() const;
		int getPlayerNumber() const;
		int getTeamNumber() const;

		int getHealth() const;
		void setHealth(const int newHealth);

		int getScore() const;
		void setScore(const int newScore);

		int getShots() const;
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

class weaponSettings {
	private:
		std::array<const char *, 5> weaponNames = 	{	"Shotgun", "Pistol", 	"Sniper", 	"AK-47", 	"M16"	};
		std::array<int, 5> damageFactors = 			{		10,		1, 			5, 			6, 			6		};
		std::array<int, 5> bulletsPerMag = 			{		6,		17, 		5, 			30, 		30		};
		std::array<int, 5> maxShotsPerTenSeconds = 	{		40, 	100, 		20,			100, 		140		};
		std::array<bool, 5> autoAllowed = 			{		false, 	false, 		false, 		true, 		true	};
		std::array<bool, 5> semiAllowed = 			{		false, 	false, 		false, 		true, 		true	};
	public:
		const char * getName(const int weaponId) const;
		const int getDamage(const int weaponId, const int distance) const;
		const int getBulletsPerMag(const int weaponId) const;
		const int maxShotsPerTime(const int weaponId) const;
		const bool autoAllowedForWeapon(const int weaponId) const;
		const bool semiAllowedForWeapon(const int weaponId) const;
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
		const bool semiAllowed() const;

		friend hwlib::ostream& operator<<(hwlib::ostream & stream, const weaponData & weapon){
			stream << hwlib::left << "Statistics of weapon " << weapon.getName() << " with ID " << weapon.getId() << "." << hwlib::endl;
			stream << hwlib::setw(30) << "Bullets: " << weapon.getAmountOfBullets() << hwlib::endl;
			stream << hwlib::setw(30) << "Magazines: " << weapon.getAmountOfMags() << hwlib::endl;
			stream << hwlib::setw(30) << "Max shots per second: " << int(weapon.maxShotsPerTenSeconds() / 10) << hwlib::endl;
			stream << hwlib::setw(30) << "Semi Allowed: " << hwlib::boolalpha << weapon.semiAllowed() << hwlib::endl;
			stream << hwlib::setw(30) << "Auto Allowed: " << hwlib::boolalpha << weapon.autoAllowed() << hwlib::endl;
			stream << hwlib::setw(30) << "Damagefactor: " << hwlib::boolalpha << weapon.getDamage() << hwlib::endl;
			return stream;
		}
};

class displayedData {
	public:
		int lastBullets = 0;
		int lastHealth = 100;
		int lastScore = 0;
		int lastWeaponId = 0;
};


#endif //__ENTITIES_HPP