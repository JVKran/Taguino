#include "hwlib.hpp"
#include "receiver.hpp"

class messageLogger : public messageListener {
public:
    virtual void messageReceived(const uint16_t message) override{
      hwlib::cout << int(message) << hwlib::endl;
    }
};


int main( void ){	
  hwlib::wait_ms(500);

  messageLogger logger = messageLogger();
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
