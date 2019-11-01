#include "mp3.hpp"
#include "hwlib.hpp"
#include <array>

//Als uart niet werkt, io mode gebruiken, veel makkelijker. Adkey1 om te resetten naar eerst lied, daarna met IO 2 verder gaan.
int main(){
	hwlib::wait_ms(4000);

		mp3 afspeler;
		hwlib::cout<<"playing";
		afspeler.playSound(1);

}