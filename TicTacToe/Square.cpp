#include"Square.h"

Square :: Square() = default;

Square :: Square(float x, float y)
{
	x_coordinate = x;
	y_coordinate = y;

	//Default Length And Width...Never Changes
	length = 0.666f;
	width  = 0.666f;

	//Calculate The Center of Square
	x_center = x_coordinate + (width / 2);
	y_center = y_coordinate - (length /2);

	//Figure Has Not Yet Been Determined
	figure = Undetermined;

	//Color Of The Figure Is Black.. Match Background
	red   = 0.0f;
	green = 0.0f;
	blue  = 0.0f;
}

void Square :: setShape(shape figure)
{
	this->figure = figure;
}

void Square :: setColors(float r, float g, float b)
{
	red   = r;
	green = g;
	blue  = b;
}

//Coordinate Getters
float Square :: getX(){return x_coordinate;}

float Square :: getY(){return y_coordinate;}

float Square :: getCenterX(){return x_center;}

float Square :: getCenterY(){return y_center;}

//Shape Type Getter
shape Square :: getShapeType(){return figure;}

//Color Getter
float Square :: getRed(){return red;}

float Square :: getGreen(){return green;}

float Square :: getBlue(){return blue;}

//Special Function To Check If Mouse Coordinates Are in Square
bool Square :: contains(float mx, float my)
{
	if((mx > x_coordinate) && (mx < (x_coordinate + width)))
	{
		if((my < y_coordinate) && (my > (y_coordinate - length)))
			return true;
	}
	
	return false;
} 
