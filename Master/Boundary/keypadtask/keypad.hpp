#ifndef __T9_KEYS_HPP
#define __T9_KEYS_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
class keypadListener {
public:
    virtual void keyPressed(char karakter) = 0;
};
class testlistner : public keypadListener{
     void keyPressed (char karakter);
};

class T9Keys  {
	private:



		hwlib::target::pin_oc out0 = hwlib::target::pin_oc( hwlib::target::pins::d51 );
		hwlib::target::pin_oc out1 = hwlib::target::pin_oc( hwlib::target::pins::d49);
		hwlib::target::pin_oc out2 = hwlib::target::pin_oc( hwlib::target::pins::d47 );
		hwlib::target::pin_oc out3 = hwlib::target::pin_oc( hwlib::target::pins::d45 );

		hwlib::target::pin_in in0  = hwlib::target::pin_in( hwlib::target::pins::d43 );
		hwlib::target::pin_in in1  = hwlib::target::pin_in( hwlib::target::pins::d41);
		hwlib::target::pin_in in2  = hwlib::target::pin_in( hwlib::target::pins::d39);
		hwlib::target::pin_in in3  = hwlib::target::pin_in( hwlib::target::pins::d37 );
		
		hwlib::port_oc_from_pins_t  out_port = hwlib::port_oc_from_pins_t( out0, out1, out2, out3 );
		hwlib::port_in_from_pins_t  in_port  = hwlib::port_in_from_pins_t( in0,  in1,  in2,  in3  );
		hwlib::matrix_of_switches   matrix   = hwlib::matrix_of_switches( out_port, in_port );
   		hwlib::keypad<16> numpad   = hwlib::keypad< 16 >( matrix, "147*2580369#ABCD" );

		uint_fast64_t lastKeyPress;
		uint_fast64_t keyPressPeriod;

		char lastCharacter;				//Lastly returned char; after T9-Simulation.
		char lastKey;					//Lastly pressed key; before T9-Simulation.
		char newCharacter;				//Newly received char; before T9-Simulation (result of getc())
		unsigned int letterIncrements;	//Amount of double presses; equal to amount of increments (from a to b and c).

        char karakter =0;
        char i;
        uint8_t count=0;
        uint_fast64_t lastpress= hwlib::now_us();
		bool returned=0;
		int multiplier=0;
		int maxcount=2;


		//rtos::clock updateClock;
        keypadListener* listen;
	public:
		T9Keys(keypadListener* listen/*,unsigned long long int period = 10'000, const char * name = "Input Handler"*/);

		char readChar();
		char readKey();

		void debug();

		
		void update();
		//void main() override;
};

#endif //__INPUT_HPP