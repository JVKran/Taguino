#include "433mhz.hpp"
#include "hwlib.hpp"
int main(){
	namespace target = hwlib::target;
	
	auto receive = target::pin_in ( target::pins::d15);


	auto receiveIt = receiver( receive );
	
	for(;;){
		hwlib::wait_ms(1);
		hwlib::cout << "nothing\n";
		auto val = receiveIt.readUint(true);
		hwlib::cout<<val;
		hwlib::cout<<"nothingAgaain\n";
		
	}
}
