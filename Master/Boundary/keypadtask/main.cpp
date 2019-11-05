#include "hwlib.hpp"
#include "keypad.hpp"


// int main( void ){	
//    namespace target = hwlib::target;  

//    auto out0 = target::pin_oc( target::pins::d51 );
//    auto out1 = target::pin_oc( target::pins::d49);
//    auto out2 = target::pin_oc( target::pins::d47 );
//    auto out3 = target::pin_oc( target::pins::d45 );

//    auto in0  = target::pin_in( target::pins::d43 );
//    auto in1  = target::pin_in( target::pins::d41);
//    auto in2  = target::pin_in( target::pins::d39);
//    auto in3  = target::pin_in( target::pins::d37 );
   
//    auto out_port = hwlib::port_oc_from_pins_t( out0, out1, out2, out3 );
//    auto in_port  = hwlib::port_in_from_pins_t( in0,  in1,  in2,  in3  );
//    auto matrix   = hwlib::matrix_of_switches( out_port, in_port );
//    auto numpad   = hwlib::keypad< 16 >( matrix, "147*2580369#ABCD" );
//    //auto numpad   = hwlib::keypad< 16 >( matrix, "47258" );
//   //auto numpad   = hwlib::keypad< 16 >( matrix, "A47B2458B369C*0#D" );


//    keyboard keypad = keyboard(numpad);
//    char readChar;
   
   
   
//    while(true){
//       readChar = keypad.readChar();
//       if(readChar != '\0'){
//          hwlib::cout << readChar << hwlib::endl;
//       }
//    }
   
// }
    //keypadListener testlisten;

int main(){
testlistner test;
T9Keys toetsenbord(&test);
hwlib::wait_ms(500);
rtos::run();

}
