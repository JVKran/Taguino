#include "hwlib.hpp"
#include "transmitter.hpp"

#include <array>

class tester : public rtos::task<> {
private:
	infraredTransmitter & Transmitter;
	rtos::clock testClock;
public:
	tester(infraredTransmitter & Transmitter):
		Transmitter(Transmitter),
		testClock(this, 1'000'000, "TestClock")
	{}

	void main() override{
		for(;;){
			wait(testClock);
			Transmitter.sendData(43643);
		}
	}
};

int main( void ){	
	hwlib::wait_ms( 500 );

	auto Transmitter = infraredTransmitter();
	auto logger = tester(Transmitter);

	rtos::run();
}
