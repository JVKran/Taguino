#include "hwlib.hpp"
#include <array>

class weapon{
private:
	int weaponID;
	std::array<int, 3> magSize;
	int bulletAmount;
	std::array<int, 3> damageFactor;
public:
	weapon()
	{
		std::array<int, 3> magSize = {4, 12, 30};
		hwlib::wait_ms(500);
		hwlib::cout<<"mag1: "<<magSize[0]<<hwlib::endl;
		hwlib::cout<<"mag2: "<<magSize[1]<<hwlib::endl;
	}
};