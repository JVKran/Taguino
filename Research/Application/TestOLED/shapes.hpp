#ifndef __SHAPES_HPP
#define __SHAPES_HPP

#include "hwlib.hpp"

class rectangle{
private:
	hwlib::window & window;
	hwlib::xy & startRectangle;
	hwlib::xy & endRectangle;
public:
	rectangle(hwlib::window & window, hwlib::xy & startRectangle, hwlib::xy & endRectangle):
		window(window),
		startRectangle(startRectangle),
		endRectangle(endRectangle)
	{}

	void print();
};

#endif /*shapes.hpp*/