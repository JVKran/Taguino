#include "hwlib.hpp"
#include "rtos.hpp"
#include "runGame.hpp"

runGame::runGame(display& d, rotaryEncoder& re, keypad& kp):
	task("runGame", 3),
	toetsChannel(this, "toetsChannel");
	receiveMessageChannel(this, "receiveMessageChannel");
	newPlayerPool(this, "newPlayerPool");
	newPlayerFlag(this, "newPlayerFlag")
	oled(d);
	encoder(re);
	key(kp);
{};

void runGame::changeScoreboard(){

}

void runGame::keyPressed(int nr){
	toetsChannel.write(keypadID);
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