#include "signup.hpp"

signUp::signUp(NRF24 & radio):
	radio(radio)
{}

void signUp::dataReceived(const uint8_t data[], const int len){
	if(data[0] == 1){
		for(auto & element : onlineWeapons){
			if(element != 0){
				element = data[1];
			}
		}
	}
}