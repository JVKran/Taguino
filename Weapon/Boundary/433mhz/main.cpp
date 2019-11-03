#include "serial.hpp"
#include "hwlib.hpp"
#include <array>

//Als uart niet werkt, io mode gebruiken, veel makkelijker. Adkey1 om te resetten naar eerst lied, daarna met IO 2 verder gaan.
int main(){
	hwlib::wait_ms(3000);
    		hwuart transceiver;
            uint16_t data =12345;
        
        // transmitting code, usefull for testing purpose and as example for what would be in the grenade
        /*

        
		for(;;){
            hwlib::wait_ms(500);
            transceiver.put_uint(data);
        }
        hwlib::cout<<"sending"<<hwlib::endl;
        }
        */
       //receiving code for the weapon 
       for(;;){

           data = transceiver.get_uint();
               hwlib::cout<<hwlib::endl<<hwlib::endl<<hwlib::endl;
               hwlib::wait_us(800);
       }
       
}