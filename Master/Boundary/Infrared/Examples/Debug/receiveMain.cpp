#include "hwlib.hpp"
#include "receiver.hpp"

int main( void ){	

  auto scl      = hwlib::target::pin_oc{ hwlib::target::pins::scl };
  auto sda      = hwlib::target::pin_oc{ hwlib::target::pins::sda };
   
  auto i2c_bus  = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
  auto oled     = hwlib::glcd_oled_i2c_128x64_direct( i2c_bus ); 
  oled.clear();

  auto timeWindow = hwlib::window_part(oled, hwlib::xy(0, 0), hwlib::xy(50, 16));
  auto timeFont = hwlib::font_default_16x16();
  auto timeField = hwlib::terminal_from(timeWindow, timeFont);

  auto irReceiverPin = hwlib::target::pin_in(hwlib::target::pins::d5);
  auto irReceiver = receiver(irReceiverPin);
  auto receptionPin = hwlib::target::pin_out(hwlib::target::pins::d7);

  char receivedCharacter;
  uint_fast64_t howLongAgo = hwlib::now_us();

  for(;;){
  	if(irReceiver.dataAvailable()){
  		receivedCharacter = irReceiver.readChar();
     	timeField << "\f" << receivedCharacter  << hwlib::endl;
     	if(receivedCharacter == 'j' || receivedCharacter == 'a' || receivedCharacter == 'w' || receivedCharacter == 'o' || receivedCharacter == 'e' || receivedCharacter == 'l'){
			  receptionPin.write(1);
			  howLongAgo = hwlib::now_us();
    	}
  	}
  	if(hwlib::now_us() - howLongAgo > 500'000){
  		receptionPin.write(0);
  		receptionPin.flush();
  	}
  }
}
