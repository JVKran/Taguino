#include "entities.hpp"

const char * playerData::getName() const {
	return name;
}

void playerData::setName(const char newName[8]){
	for(unsigned int i = 0; i < 8; i++){
		name[i] = newName[i];
	}
}

uint8_t playerData::getPlayerNumber() const {
	return playerNumber;
}

void playerData::setPlayerNumber(const uint8_t newPlayerNumber){
	playerNumber = newPlayerNumber;
}

uint8_t playerData::getTeamNumber() const {
	return teamNumber;
}

void playerData::setTeamNumber(const uint8_t newTeamNumber){
	teamNumber = newTeamNumber;
}

uint8_t playerData::getHealth() const {
	return health;
}

void playerData::setHealth(const int newHealth){
	health = newHealth;
}

uint8_t playerData::getScore() const {
	return score;
}

void playerData::setScore(const int newScore){
	score = newScore;
}

uint8_t playerData::getShots() const {
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
	if(weaponId == 0){
		return (weaponId == 1) ? damageFactors[weaponId] * (distance / 10) : damageFactors[weaponId];
	} else {
		return damageFactors[0];
	}
}

const int weaponSettings::getBulletsPerMag(const int weaponId) const {
	return bulletsPerMag[weaponId];
}

const int weaponSettings::getAmountOfMags(const int weaponId) const{
	return amountOfMags[weaponId];
}

const int weaponSettings::maxShotsPerTime(const int weaponId) const {
	return maxShotsPerTenSeconds[weaponId];
}

const bool weaponSettings::autoAllowedForWeapon(const int weaponId) const {
	return autoAllowed[weaponId];
}

const bool weaponSettings::burstAllowedForWeapon(const int weaponId) const {
	return burstAllowed[weaponId];
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

unsigned int weaponData::getAmountOfBullets() const {
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

const unsigned int weaponData::maxShotsPerTenSeconds() const {
	return weapons.maxShotsPerTime(id);
}

const bool weaponData::autoAllowed() const {
	return weapons.autoAllowedForWeapon(id);
}

const bool weaponData::burstAllowed() const {
	return weapons.burstAllowedForWeapon(id);
}

const int weaponData::bulletsPerMag() const {
	return weapons.getBulletsPerMag(id);
}







