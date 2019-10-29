#include "scoreboard.hpp"

scoreboard::scoreboard(hwlib::window & window, hwlib::glcd_oled & oled):
	window(window),
	oled(oled)
{
	auto windowFont 			= hwlib::font_default_8x8();
	auto windowName 			= hwlib::window_part(window, hwlib::xy(114, 3), hwlib::xy(128, 12));
	hwlib::circle nameCircle	= hwlib::circle(hwlib::xy(117, 6), 5);
	nameCircle.draw(oled);
	auto windowNameTerminal 	= hwlib::terminal_from(windowName, windowFont);

	auto windowPartFirstPlace 	= hwlib::window_part(window, hwlib::xy(0,10), hwlib::xy(124, 20));
	auto windowPartSecondPlace 	= hwlib::window_part(window, hwlib::xy(0,21), hwlib::xy(124, 31));
	auto windowPartThirdPlace 	= hwlib::window_part(window, hwlib::xy(0,32), hwlib::xy(124, 42));
	auto windowPartFourthPlace 	= hwlib::window_part(window, hwlib::xy(0,43), hwlib::xy(124, 53));
	auto windowPartFifthPlace 	= hwlib::window_part(window, hwlib::xy(0,54), hwlib::xy(124, 64));

	auto terminalFirstPlace 	= hwlib::terminal_from(windowPartFirstPlace, windowFont);
	auto terminalSecondPlace 	= hwlib::terminal_from(windowPartSecondPlace, windowFont);
	auto terminalThirdPlace 	= hwlib::terminal_from(windowPartThirdPlace, windowFont);
	auto terminalFourthPlace 	= hwlib::terminal_from(windowPartFourthPlace, windowFont);
	auto terminalFifthPlace 	= hwlib::terminal_from(windowPartFifthPlace, windowFont);


	terminalFirstPlace 	<< hwlib::left <<hwlib::setw(11) <<"Kapitein" << 59;
	terminalSecondPlace << hwlib::left <<hwlib::setw(11) << "Dr Iglo" << 35;
	terminalThirdPlace 	<< hwlib::left <<hwlib::setw(11) << "Player3" << 24;
	terminalFourthPlace << hwlib::left <<hwlib::setw(11) << "Player4" << 12;
	terminalFifthPlace 	<< hwlib::left <<hwlib::setw(11) << "Player5" << 02;
	windowNameTerminal 	<< 'G';
	windowNameTerminal.flush();
}

scoreboardLine::scoreboardLine(hwlib::window & nameWindow, hwlib::window & scoreWindow):
	nameWindow(nameWindow),
	scoreWindow(scoreWindow)
{
	
}
