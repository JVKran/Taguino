#include "hwlib.hpp"
#include "rtos.hpp"
#include "runGame.hpp"

runGame::runGame(display& d, rotaryEncoder& re, keypad& kp):
	task("runGame", 1),
	toetsChannel(this, "toetsChannel");
	receiveMessageChannel(this, "receiveMessageChannel");
	oled(d);
	encoder(re);
	key(kp);
{};

void runGame::damageDone(uint8_t damage){

}

void runGame::keyPressed(){

}

void runGame::encoderPressed(){

}

void runGame::encoderTurnedToPos(int pos){

}

void runGame::startGame(){

}

void runGame::addPlayer(){
	
}

void runGame::decodeMessage(){

}

void runGame::main(){

}