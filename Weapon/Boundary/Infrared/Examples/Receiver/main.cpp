#include "hwlib.hpp"
#include "transceiver.hpp"

int main( void ){	

  hwlib::wait_ms(500);

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

  uint16_t receivedNumber;
  uint_fast64_t howLongAgo = hwlib::now_us();

  for(;;){
  	if(irReceiver.dataAvailable()){
  		receivedNumber = irReceiver.readData();
     	if(receivedNumber == 43643){
			  receptionPin.write(1);
			  howLongAgo = hwlib::now_us();
    	}
      hwlib::cout << "Main Received: " << int(receivedNumber) << hwlib::endl << hwlib::endl;
  	}
  	if(hwlib::now_us() - howLongAgo > 500'000){
  		receptionPin.write(0);
  		receptionPin.flush();
  	}
  }
}
