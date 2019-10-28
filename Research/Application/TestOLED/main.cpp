#include "hwlib.hpp"
#include "weapon.hpp"
#include "display.hpp"

int main(){
	auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
	auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
	auto i2cBus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
	auto oled = hwlib::glcd_oled(i2cBus);

	auto Display = display(oled);
	oled.clear();
	
	Display.showWeapon(1);
	Display.showBullets(4);
	Display.showMagazines(3);
	Display.showHealthBar();
	hwlib::wait_ms(200);
	for(int i=100; i>0;--i){
		Display.updateHealth(i+1,i);
	}

	// Display.terminal();
	// weapon wapen = weapon();
	
}