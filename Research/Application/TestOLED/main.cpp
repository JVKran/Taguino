#include "hwlib.hpp"
#include "weapon.hpp"

int main(){
	auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
	auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);

	auto i2cBus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
	auto oled = hwlib::glcd_oled(i2cBus);

	auto weaponWindow = hwlib::window_part(oled, hwlib::xy(0,0), hwlib::xy(40,13));
	auto bulletsWindow = hwlib::window_part(oled, hwlib::xy(0,14), hwlib::xy(41,24));

	shotgun shottie = shotgun(weaponWindow, bulletsWindow);

	oled.clear();
	shottie.drawWeapon();
	shottie.drawBullets();
}