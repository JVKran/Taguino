#include "playerData.hpp"

playerData::playerData(const char * name, const int playerNumber, const int teamNumber):
	name(name),
	playerNumber(playerNumber),
	teamNumber(teamNumber)
{}

const char * playerData::getName() const {
	return name;
}

uint8_t playerData::getPlayerNumber() const {
	return playerNumber;
}

uint8_t playerData::getTeamNumber() const {
	return teamNumber;
}

uint8_t playerData::getHealth() const {
	return health;
}

void playerData::setHealth(uint8_t newHealth) {
	health = newHealth;
}

uint16_t playerData::getShots() const {
	return shots;
}

void playerData::setShots(){
	shots++;
}

uint16_t playerData::getDamage() const {
	return damage;
}

void playerData::setDamage(uint8_t damageDealt) {
	damage += damageDealt;
}

uint8_t playerData::getKills() const {
	return kills;
}

void playerData::setKills() {
	kills++;
}

uint8_t playerData::getDeaths() const {
	return deaths;
}

void playerData::setDeaths() {
	deaths++;
}

uint16_t playerData::getScore() const {
	return score;
}

void playerData::setScore(uint8_t addScore){
	score += newScore;
}