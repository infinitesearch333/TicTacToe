#ifndef Square_h
#define Square_h

//Using enum to avoid confusion.
// Enum specifies the type of shape within a square
enum shape{Undetermined = 0, X = 1, O = 2};

class Square
{

private:
	//Coordinates for the top left corner of square 
	float x_coordinate;
	float y_coordinate;

	//Dimension of the square
	float length;
	float width;

	//Coordinates for the center of the square
	float x_center;
	float y_center;

	//Shape inside square
	shape figure;

	//Color of the figure bounded by square
	float red;
	float green;
	float blue;

public:
	//Default Constructor
	Square();
	//Overloaded Constructor
	Square(float x, float y);

	//Necessary Setters
	void setShape(shape figure);
	void setColors(float r, float g, float b);

	//Necessary Getters
	float getX();
	float getY();
	float getCenterX();
	float getCenterY();
	shape getShapeType();
	float getRed();
	float getGreen();
	float getBlue();

	//Function Determines If Mouse Coordinates are within square
	bool contains(float mx, float my);
};



#endif

