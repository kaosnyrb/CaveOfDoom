//----------------------------------------------------------
// A 2d vector, storing information for all your 2d vectory needs
// Bryn Stringer 
//----------------------------------------------------------
#include "util_vector2d.h"

util_vector2d::util_vector2d(void)
{
}

util_vector2d::util_vector2d(int xvalue, int yvalue)
{
	x = xvalue;
	y = yvalue;
}

util_vector2d::~util_vector2d(void)
{
}

util_vector2d util_vector2d::operator +(util_vector2d input)
{
	int tempx = x + input.x;
	int tempy = y + input.y;
	util_vector2d temp(tempx,tempy);
	return temp;
}
