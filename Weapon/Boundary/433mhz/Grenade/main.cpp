#include "serial.hpp"
#include "hwlib.hpp"
#include <array>

int main(){
	hwlib::wait_ms(500);
    		hwuart afspeler;
        
        
        uint8_t testArray[10] = { 0xFF, 0xFF, 0xFF, 0x03, 0x01, 0x01, 0x05, 0xFF, 0xFF, 0xEF };
        
		for(;;){
            hwlib::wait_ms(500);
        for(int i=0; i<10; i++){
            afspeler.usart_putc(testArray[i]);
            hwlib::wait_us(400);
        }
        hwlib::cout<<"sending"<<hwlib::endl;
        }
        
       /*
       for(;;){
           if(afspeler.usart_getc() == 254){
               uint8_t testArray[8] = { 0, 0, 0, 0, 0, 0, 0, 0};
               for(int i=0; i<8; i++){
           testArray[i] = afspeler.usart_getc();
           hwlib::wait_us(800);
               }
               for(int i=0; i<8; i++){
           hwlib::cout<<testArray[i]<<hwlib::endl; 
           hwlib::wait_us(800);
               }
               hwlib::cout<<hwlib::endl<<hwlib::endl<<hwlib::endl;
           
       }
       
       }
       */
}