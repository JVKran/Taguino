
#include "keypad.hpp"
    void testlistner::keyPressed(char karakter){
        hwlib::cout<<karakter<<hwlib::endl;
    }


T9Keys::T9Keys(keypadListener* listen/*,unsigned long long int period, const char * name*/):
	//task(name),
	//updateClock(this, period, "Update Clock"),
    listen(listen)
{}





void T9Keys::update(){
               //HWLIB_TRACE;
    // char karakter;
    // char i;
    // uint8_t count=0;
    // bool returned=0;
    // int multiplier=0;
    // int maxcount=2;
    // uint_fast64_t lastpress= hwlib::now_us();
	//for(;;){
	//	wait(updateClock);
        if(((hwlib::now_us()-lastpress) > 1000000)&&returned==false){
            listen->keyPressed(karakter);
            returned=true;
 
        }
        else{
        if(numpad.char_available()){
            hwlib::wait_ms(10);
            if((hwlib::now_us()-lastpress) > 1000000){
                returned= false;
                count=0;

                
                i=numpad.getc();
                lastpress=hwlib::now_us();
                if(i=='7'){
                    multiplier=0;
                    maxcount= 3;
                }
                else if(i =='8'){
                    maxcount=2;
                    multiplier=1;
                }
                else if(i=='9')
                {
                    multiplier=1;
                    maxcount=3;
                }
                
                else
                {
                    maxcount=2;
                    multiplier=0;
                }
                if(int(i)>0){
                    karakter= (((i - '0') - 2) * 3) + 97+multiplier;
                    //hwlib::cout<<karakter<<hwlib::endl;
                }
        }
        else
        {
            hwlib::wait_ms(10);

            if((numpad.getc()==i)&&(count<maxcount)){
                count++;
                karakter+=1;
                //hwlib::cout<<karakter<<hwlib::endl;

            }
            else{
                lastpress=0;
            }
        



        }
        }
    }
    }
        
        

//}




char T9Keys::readChar(){
    
	//if(numpad.char_available()){

        return 0;
        
	// 	newCharacter = numpad.getc();
	// 	keyPressPeriod = hwlib::now_us() - lastKeyPress;
	// 	lastKeyPress = hwlib::now_us();
	// 	lastKey = newCharacter;
	// 	lastCharacter = (((newCharacter - '0') - 2) * 3) + 97;
	// 	//hwlib::wait_ms(200);
	// 	// while(hwlib::now_us() - lastKeyPress < 500'000){
	// 	// 	if(numpad.char_available()){
	// 	// 		newCharacter = numpad.getc();
	// 	// 		if(newCharacter != '\0' && letterIncrements < 2 && newCharacter == lastKey && newCharacter < '7'){
	// 	// 			lastCharacter++;
	// 	// 			letterIncrements++;
	// 	// 			lastKeyPress = hwlib::now_us();
	// 	// 			hwlib::wait_ms(100);
	// 	// 		} else if(newCharacter == '7' && letterIncrements < 3 && newCharacter == lastKey){
	// 	// 			lastCharacter++;
	// 	// 			letterIncrements++;
	// 	// 			lastKeyPress = hwlib::now_us();
	// 	// 			hwlib::wait_ms(100);
	// 	// 		} else if(newCharacter == '8' && letterIncrements < 2 && newCharacter == lastKey){
	// 	// 			lastCharacter++;
	// 	// 			letterIncrements++;
	// 	// 			lastKeyPress = hwlib::now_us();
	// 	// 			hwlib::wait_ms(100);
	// 	// 		} else if(newCharacter == '9' && letterIncrements < 3 && newCharacter == lastKey){
	// 	// 			lastCharacter++;
	// 	// 			letterIncrements++;
	// 	// 			lastKeyPress = hwlib::now_us();
	// 	// 			hwlib::wait_ms(100);
	// 	// 		} else {
	// 	// 			break; 
	// 	// 		}
	// 	// 	}
	// 	// }
	// 	letterIncrements = 0;
	// 	return lastCharacter;
	// } else {
	// 	return 0;
	// }
}

/// \brief
/// Read Key
/// \details
/// This function returns the character of the pressed key equal to the one drawn on the numpad.
char T9Keys::readKey(){
	return numpad.pressed();
}

/// \brief
/// Debug
/// \details
/// This function can be used for debugging. It prints the amount of presses that have been done
/// and the pressed key.
void T9Keys::debug(){
   	int n = 0;
   	for(;;){
	   	if(numpad.char_available()){
	   		hwlib::cout << n++ << " [" << numpad.getc() << "]\n";
	   	}
   	}
}