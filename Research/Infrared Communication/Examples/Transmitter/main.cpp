#include "hwlib.hpp"
#include "transmitter.hpp"

#include <array>

class tester : public rtos::task<> {
private:
	infraredEncoder & encoder;
	rtos::clock testClock;
public:
	tester(infraredEncoder & encoder):
		encoder(encoder),
		testClock(this, 1'000'000, "TestClock")
	{}

	void main() override{
		for(;;){
			wait(testClock);
			encoder.sendData(43643);
			hwlib::cout << "Sent data" << hwlib::endl;
		}
	}
};

int main( void ){	
	hwlib::wait_ms( 500 );

	auto encoder = infraredEncoder();
	auto logger = tester(encoder);

	rtos::run();
}
