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

  uint16_t receivedNumber;

  for(;;){
  	if(irReceiver.dataAvailable()){
  		receivedNumber = irReceiver.readData();
<<<<<<< HEAD
      hwlib::cout << "Data Received: " << int(receivedNumber) << hwlib::endl;
      // hwlib::cout << "Distance: " << (receivedNumber & 0x3F) * 10 << "cm. "<< hwlib::endl;
      // hwlib::cout << "Playernumber: " << (receivedNumber >> 10) << hwlib::endl;
      // hwlib::cout << "Weapon: " << ((receivedNumber & 0x1C0) >> 6);
=======
      // hwlib::cout << "Data Received: " << int(receivedNumber) << hwlib::endl;
      // hwlib::cout << "Distance: " << (receivedNumber & 0x3F) * 10 << "cm. "<< hwlib::endl;
      // hwlib::cout << "Playernumber: " << (receivedNumber >> 10) << hwlib::endl;
      // hwlib::cout << "Weapon: " << ((receivedNumber & 0x1C0) >> 6);
      hwlib::cout<<int(receivedNumber)<<'\n';
>>>>>>> 5b8c7489724b7c77911850b09db0b880c78a39b2
  	}
  }
}
