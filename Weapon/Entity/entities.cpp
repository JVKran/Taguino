#include "entities.hpp"

playerData::playerData(const char * name, const int playerNumber, const int teamNumber):
	name(name),
	playerNumber(playerNumber),
	teamNumber(teamNumber)
{}

const char * playerData::getName() const {
	return name;
}

int playerData::getPlayerNumber() const {
	return playerNumber;
}

int playerData::getTeamNumber() const {
	return teamNumber;
}

int playerData::getHealth() const {
	return health;
}

void playerData::setHealth(const int newHealth){
	health = newHealth;
}

int playerData::getScore() const {
	return score;
}

void playerData::setScore(const int newScore){
	score = newScore;
}

int playerData::getShots() const {
	return shots;
}

void playerData::setShots(const int newShots){
	shots = newShots;
}


//<<<<<<<<--------------------------------------------------------------------------------------->>>>>>>>>>>>>>>>>>


const char * weaponSettings::getName(const int weaponId) const {
	return weaponNames[weaponId];
}

const int weaponSettings::getDamage(const int weaponId, const int distance) const {
	return damageFactors[weaponId] * distance;
}

const int weaponSettings::maxShotsPerTime(const int weaponId) const {
	return maxShotsPerTenSeconds[weaponId];
}

const bool weaponSettings::autoAllowedForWeapon(const int weaponId) const {
	return autoAllowed[weaponId];
}

const bool weaponSettings::semiAllowedForWeapon(const int weaponId) const {
	return semiAllowed[weaponId];
}



//<<<<<<<<<<<<<---------------------------------------------------------------------------------->>>>>>>>>>>>>>>>>>>

weaponData::weaponData(const int id, const int amountOfMags, const int bulletAmount):
	id(id),
	amountOfMags(amountOfMags),
	bulletAmount(bulletAmount)
{}

int weaponData::getId() const {
	return id;
}

void weaponData::setId(const int newId){
	id = newId;
}

int weaponData::getAmountOfMags() const {
	return amountOfMags;
}

void weaponData::setAmountOfMags(const int newAmount){
	amountOfMags = newAmount;
}

int weaponData::getAmountOfBullets() const {
	return bulletAmount;
}

void weaponData::setAmountOfBullets(const int newAmountOfBullets){
	bulletAmount = newAmountOfBullets;
}

const char * weaponData::getName() const {
	return weapons.getName(id);
}

const int weaponData::getDamage(const int distance) const {
	return weapons.getDamage(id, distance);
}

const int weaponData::maxShotsPerTenSeconds() const {
	return weapons.maxShotsPerTime(id);
}

const bool weaponData::autoAllowed() const {
	return weapons.autoAllowedForWeapon(id);
}

const bool weaponData::semiAllowed() const {
	return weapons.semiAllowedForWeapon(id);
}







