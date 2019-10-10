#ifndef __SHOOTDATA_HPP
#define __SHOOTDATA_HPP
#include "hwlib.hpp"


class shootdata{
uint16_t data;
void controlBit();
public:
void sendData(int playerNumber,int distance, int weapon);







};


#endif //__SHOOTDATA_HPP