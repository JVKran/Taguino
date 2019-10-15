#include "hwlib.hpp"
#include "weapon.hpp"
#include "shotgun.hpp"
#include "pistol.hpp"

int main(){
	auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
	auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);

	auto i2cBus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
	auto oled = hwlib::glcd_oled(i2cBus);

	auto upperWindow = hwlib::window_part(oled, hwlib::xy(0, 0), hwlib::xy(128, 32));
	auto upperWindowFont = hwlib::font_default_8x8();
	auto upperConsole = hwlib::terminal_from(upperWindow, upperWindowFont);

	auto weaponWindow = hwlib::window_part(oled, hwlib::xy(0,0), hwlib::xy(40, 17));
	// auto weaponFont = hwlib::font_default_8x8();
	// auto weaponConsole = hwlib::terminal_from(weaponWindow, weaponFont);

	
	shotgun shottie = shotgun(weaponWindow);
	pistol handGun = pistol(weaponWindow);
	oled.clear();
	shottie.drawWeapon();
	// handGun.drawWeapon();
}