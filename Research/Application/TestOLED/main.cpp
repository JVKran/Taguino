#include "hwlib.hpp"

int main(){
	auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
	auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);

	auto i2cBus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
	auto oled = hwlib::glcd_oled(i2cBus);

	auto upperWindow = hwlib::window_part(oled, hwlib::xy(0, 0), hwlib::xy(128, 32));
	auto upperWindowFont = hwlib::font_default_8x8();
	auto upperConsole = hwlib::terminal_from(upperWindow, upperWindowFont);

	auto lowerWindow = hwlib::window_part(oled, hwlib::xy(0, 32), hwlib::xy(128, 64));
	auto lowerWindowFont = hwlib::font_default_16x16();
	auto lowerConsole = hwlib::terminal_from(lowerWindow, lowerWindowFont);

	upperConsole << "\f" << "upper window" << "\n" << hwlib::flush;
	lowerConsole << "\f" << "lower window" << "\n" << hwlib::flush;
}