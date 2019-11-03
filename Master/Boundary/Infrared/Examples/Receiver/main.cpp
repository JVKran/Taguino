#include "hwlib.hpp"
#include "receiver.hpp"

class messageLogger : public messageListener {
private:
  hwlib::terminal & messageTerminal;
public:
  messageLogger(hwlib::terminal & messageTerminal):
    messageTerminal(messageTerminal)
  {}

  virtual void messageReceived(const uint16_t message) override{
    hwlib::cout << '\f' << int(message) << hwlib::endl;
  }
};


int main( void ){
  auto scl      = hwlib::target::pin_oc{ hwlib::target::pins::scl };
  auto sda      = hwlib::target::pin_oc{ hwlib::target::pins::sda };
   
  auto i2c_bus  = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
  auto oled     = hwlib::glcd_oled_i2c_128x64_direct( i2c_bus ); 
  oled.clear();

  auto timeWindow = hwlib::window_part(oled, hwlib::xy(0, 0), hwlib::xy(50, 16));
  auto timeFont = hwlib::font_default_8x8();
  auto timeField = hwlib::terminal_from(timeWindow, timeFont);

  messageLogger logger = messageLogger(timeField);
  infraredDecoder decoder = infraredDecoder(logger);
  infraredReceiver receiver = infraredReceiver(decoder);
  // for(;;){
  // 	if(irReceiver.dataAvailable()){
  // 		receivedNumber = irReceiver.readData();
  //     hwlib::cout << "Data Received: " << int(receivedNumber) << hwlib::endl;
  //     // hwlib::cout << "Distance: " << (receivedNumber & 0x3F) * 10 << "cm. "<< hwlib::endl;
  //     // hwlib::cout << "Playernumber: " << (receivedNumber >> 10) << hwlib::endl;
  //     // hwlib::cout << "Weapon: " << ((receivedNumber & 0x1C0) >> 6);
  // 	}
  // }
  rtos::run();
}
