#include "hwlib.hpp"
#include "button.hpp"

int main(){
    Buttoninterrupter knoppen;

    hwlib::wait_ms(500);
    for(;;){
 
        hwlib::cout<<"a9  "<<knoppen.getinterrupt1()<<hwlib::endl;
        hwlib::cout<<"a10  "<<knoppen.getinterrupt2()<<hwlib::endl;
        hwlib::cout<<"a11  "<<knoppen.getinterrupt3()<<hwlib::endl;
        hwlib::cout<<"a12  "<<knoppen.getinterrupt4()<<hwlib::endl;
        hwlib::wait_ms(1000);
    }
}