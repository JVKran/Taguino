#include "shapes.hpp"

void rectangle::draw(hwlib::window & window){
	hwlib::line(startRectangle, hwlib::xy(endRectangle.x, startRectangle.y)).draw(window);	//Top line
	hwlib::line(startRectangle, hwlib::xy(startRectangle.x, endRectangle.y)).draw(window);	//Left line
	hwlib::line(hwlib::xy(startRectangle.x, endRectangle.y), endRectangle).draw(window);	//Bottom line
	hwlib::line(hwlib::xy(endRectangle.x, startRectangle.y), endRectangle).draw(window);	//Right line
}