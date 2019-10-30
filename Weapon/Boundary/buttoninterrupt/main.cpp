#include "hwlib.hpp"
#include "button.hpp"

int main(){
    Buttoninterrupter knoppen;

    hwlib::wait_ms(500);
    for(;;){
        knoppen.refreshregister();
        hwlib::cout<<hwlib::endl<<"a9  "<<knoppen.read(17)<<hwlib::endl;
        hwlib::cout<<hwlib::endl<<"a10 "<<knoppen.read(18)<<hwlib::endl;
        hwlib::cout<<hwlib::endl<<"a11 "<<knoppen.read(19)<<hwlib::endl;
        hwlib::cout<<hwlib::endl<<"a12 "<<knoppen.read(20)<<hwlib::endl;

        hwlib::wait_ms(1000);
    }
}